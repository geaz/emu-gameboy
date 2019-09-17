import requests
import os

from bs4 import BeautifulSoup
from string import Template

opcode_url = "http://www.pastraiser.com/cpu/gameboy/gameboy_opcodes.html"
opcode_table_select = {'class': 'withborder', 'width': '1350'}

class OpcodeScraper():
    scraped_opcodes = {}

    def scrape_opcodes(self):      
        response = requests.get(opcode_url)
        soup = BeautifulSoup(response.content, 'html.parser')
        opcode_table_list = soup.find_all('table', opcode_table_select)

        for opcode_table in opcode_table_list:
            opcode_row_list = opcode_table.find_all('tr')
            
            # Skip first row (Header row)
            for i in range(1, len(opcode_row_list)):
                opcode_row = opcode_row_list[i]    
                opcode_list = opcode_row.find_all('td')

                # Iterate Columns
                for j in range(0, 16):
                    opcode = opcode_list[j+1]

                    # List contains empty entries - filter them
                    if(len(opcode.contents) > 1):
                        new_opcode = Opcode(i - 1, j, opcode)

                        if(new_opcode.mnemonic not in self.scraped_opcodes):
                            self.scraped_opcodes[new_opcode.mnemonic] = []

                        self.scraped_opcodes[new_opcode.mnemonic].append(new_opcode)


class Opcode:
    table_content = ''
    length = 0
    cycles = 0
    opcode = 0x00
    mnemonic = ''
    param1 = ''
    param2 = ''

    def __init__(self, x, y, table_content):
        self.table_content = table_content
        self.opcode = (x << 4) | y

        mnemonic = self.table_content.contents[0].split(' ')[0].strip()
        splitted_params = self.table_content.contents[0].replace(mnemonic, '').split(',')

        self.mnemonic = mnemonic
        self.param1 = splitted_params[0].strip()
        if(len(splitted_params) > 1): self.param2 = splitted_params[1].strip()

        splitted_info = self.table_content.contents[2].string.split()
        self.length = splitted_info[0].strip()
        self.cycles = splitted_info[1].strip()

    def get_opcode_as_string(self):
        return "{0:#0{1}x}".format(self.opcode,4)

    def get_target_folder(self):
        switcher = {
            'ADC': 'aritmetic', 'ADD': 'aritmetic', 'AND': 'aritmetic',
            'CCF': 'aritmetic', 'CP': 'aritmetic', 'CPL': 'aritmetic',
            'DAA': 'aritmetic', 'DEC': 'aritmetic', 'INC': 'aritmetic',
            'OR': 'aritmetic', 'SBC': 'aritmetic', 'SCF': 'aritmetic',
            'SUB': 'aritmetic', 'XOR': 'aritmetic',
            'LD': 'transfer', 'LDH': 'transfer', 'POP': 'transfer',
            'PUSH': 'transfer',
            'DI': 'misc', 'EI': 'misc', 'HALT': 'misc',
            'NOP': 'misc', 'STOP': 'misc', 'RLCA': 'misc',
            'RLA': 'misc', 'RRCA': 'misc', 'RRA': 'misc',
            'CALL': 'branch', 'JP': 'branch', 'JR': 'branch',
            'RET': 'branch', 'RETI': 'branch', 'RST': 'branch',
            'RES': 'prefix', 'BIT': 'prefix', 'SET': 'prefix',
            'RL': 'prefix', 'RLC': 'prefix', 'RR': 'prefix',
            'RRC': 'prefix', 'SLA': 'prefix', 'SRA': 'prefix',
            'SRL': 'prefix', 'SWAP': 'prefix',
        }
        return switcher.get(self.mnemonic, 'undefined')


    def display(self):
        display_string = self.get_opcode_as_string()
        display_string += ' (' + str(self.length) + ')'
        display_string += ': ' + self.mnemonic + ' ' + self.param1
        if(self.param2 != ''): display_string += ', ' + self.param2
        return display_string    

    def get_cMnemonic(self):
        result = '"' + self.mnemonic + (5 - len(self.mnemonic)) * ' '
        result += self._get_param_for_template(self.param1, self.param2 == '')

        if(self.param2 != ''):
            result += ', ' + self._get_param_for_template(self.param2, True)

        return result

    def _get_param_for_template(self, param, addApostrophe):
        result = param
        if(addApostrophe): result += '"'

        if(param == "d8"): result = '" + StringHelper::IntToHexString(opcode & 0x00FF, 2)' 
        if(param == "d16"): result = '" + StringHelper::IntToHexString(self->getAddrFrom16Bit(opcode))' 
        if(param == "a8"): result = '($FF00" + StringHelper::IntToHexString(opcode & 0x00FF, 2) + ")"' 
        if(param == "a16"): result = 'a\'" + StringHelper::IntToHexString(self->getAddrFrom16Bit(opcode))' 
        if(param == "r8"): result = 'a\'" + StringHelper::IntToHexString(opcode & 0x00FF, 2)' 

        return result


def write_template(templateFile, templateData, outputFile):
    filein = open(templateFile)
    template = Template(filein.read())
    result = template.substitute(templateData)
    filein.close()

    if not os.path.exists(os.path.dirname(outputFile)):
        os.makedirs(os.path.dirname(outputFile))

    output = open(outputFile, 'w+')
    output.write(result)
    output.close()


def get_group_output(group):
    output = ''
    for opcode in group:
        filein = open('templates/group.template')
        template = Template(filein.read())
        result = template.substitute(opcode)
        filein.close()
        output += result
    return output


scraper = OpcodeScraper()
scraper.scrape_opcodes()

if not os.path.exists('output'):
    os.makedirs('output')

for opcode_group_mnemonic, opcode_group in scraper.scraped_opcodes.items():
    mnemonic = opcode_group[0].mnemonic
    mnemonic_upper = opcode_group[0].mnemonic.upper()
    mnemonic_lower = opcode_group[0].mnemonic.lower()    
    group = []
    for opcode in opcode_group:
        group.append(
            {'opcode': opcode.get_opcode_as_string(), 'length': opcode.length, 
            'cycles': opcode.cycles, 'cMnemonic': opcode.get_cMnemonic() })

    write_template(
        'templates/instruction_header.template',
        {'mnemonic_title': mnemonic.title(), 'mnemonic_upper': mnemonic_upper },
        'output/' + opcode_group[0].get_target_folder() + '/' + mnemonic_lower + '.h')

    write_template(
        'templates/instruction.template',
        {'mnemonic_title': mnemonic.title(), 'mnemonic_lower': mnemonic_lower, 'group': get_group_output(group) },
        'output/' + opcode_group[0].get_target_folder() + '/' + mnemonic_lower + '.cpp')
