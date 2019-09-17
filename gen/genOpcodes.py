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
    mnemonicComplete = ''
    param1 = ''
    param2 = ''

    def __init__(self, x, y, table_content):
        self.table_content = table_content
        self.opcode = (x << 4) | y

        mnemonic = self.table_content.contents[0].split(' ')[0].strip()
        splitted_params = self.table_content.contents[0].replace(mnemonic, '').split(',')

        self.mnemonicComplete = self.table_content.contents[0]
        self.mnemonic = mnemonic
        self.param1 = splitted_params[0].strip()
        if(len(splitted_params) > 1): self.param2 = splitted_params[1].strip()

        splitted_info = self.table_content.contents[2].string.split()
        self.length = splitted_info[0].strip()
        self.cycles = splitted_info[1].strip()

    def get_opcode_as_string(self, prefix):
        returnValue = "{0:0{1}x}".format(self.opcode,2)
        if(prefix): returnValue = "{0:#0{1}x}".format(self.opcode,4)
        return returnValue

    def get_target_group(self):
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
            'RES': 'aritmetic', 'BIT': 'aritmetic', 'SET': 'aritmetic',
            'RL': 'aritmetic', 'RLC': 'aritmetic', 'RR': 'aritmetic',
            'RRC': 'aritmetic', 'SLA': 'aritmetic', 'SRA': 'aritmetic',
            'SRL': 'aritmetic', 'SWAP': 'aritmetic',
        }
        return switcher.get(self.mnemonic, 'undefined')  

    def display(self):
        display_string = self.get_opcode_as_string(True)
        display_string += ' (' + str(self.length) + ')'
        display_string += ': ' + self.mnemonic + ' ' + self.param1
        if(self.param2 != ''): display_string += ', ' + self.param2
        return display_string 


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


def get_rendered_template_list(items, templatePath):
    output = ''
    for item in items:
        output += get_rendered_template(item, templatePath)
    return output


def get_rendered_template(objects, templatePath):
    filein = open(templatePath)
    template = Template(filein.read())
    result = template.substitute(objects)
    filein.close()
    return result


scraper = OpcodeScraper()
scraper.scrape_opcodes()

if not os.path.exists('output'):
    os.makedirs('output')

# Group Opcode by group name
grouped_opcodes = {}
for mnemonic_name, mnemonic_group in scraper.scraped_opcodes.items():
    group_name = mnemonic_group[0].get_target_group()
    if(group_name not in grouped_opcodes):
        grouped_opcodes[group_name] = []
    grouped_opcodes[group_name].append(mnemonic_group)

instruction_items = []
for group_name, opcode_groups in grouped_opcodes.items():
    if(group_name == 'undefined'):
        print('Undefined: ' + opcode_groups[0][0].display())
        continue
    group_class_items = ''
    group_class_definitions = ''
    for opcode_group in opcode_groups:
        group_items = []
        for opcode in opcode_group:
            instruction_items.append(
                {'opcode': opcode.get_opcode_as_string(True), 'length': opcode.length, 
                'mnemonic_complete': opcode.mnemonicComplete, 
                'opcode_noprefix': opcode.get_opcode_as_string(False).upper(),
                'mnemonic_title': opcode.mnemonic.title() })
            group_items.append({
                'opcode_noprefix': opcode.get_opcode_as_string(False).upper(),
                'mnemonic_title': opcode.mnemonic.title(),
                'cycles': opcode.cycles
            })
        group_class_items += get_rendered_template_list(group_items, 'templates/group_class_items.template')
        group_class_definitions += get_rendered_template({ 
            'group_class_items': get_rendered_template_list(group_items, 'templates/group_header_class_item.template'),
            'mnemonic_title': opcode.mnemonic.title() }, 'templates/group_header_class.template')
    write_template(
        'templates/group_class.template',
        {'group_class_items': group_class_items, 'group_name': group_name },
        'output/groups/' + group_name + '.cpp')
    write_template(
        'templates/group_header.template',
        {'group_class_definitions': group_class_definitions, 'group_name_upper': group_name.upper() },
        'output/groups/' + group_name + '.h')
        
    


write_template(
    'templates/instruction_set.template',
    {'instruction_items': get_rendered_template_list(instruction_items, 'templates/instruction_set_item.template') },
    'output/instruction_set.h')