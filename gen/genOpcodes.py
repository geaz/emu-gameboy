import requests
import os

from bs4 import BeautifulSoup
from string import Template

opcode_url = "http://www.pastraiser.com/cpu/gameboy/gameboy_opcodes.html"
opcode_table_select = {'class': 'withborder', 'width': '1350'}
proxies = { } # Set a proxy, if you want to use one: 'http': 'http://ip:port'

# The OpcodeScraper collects all opcodes from the opcode_url
# The opcodes are defined in two distinct tables which get parsed by the scraper
# 'scrape_opcodes' returns a dictionary of the parsed opcodes which are grouped by there
# mnemonic. For example: scraped_opcodes = { ['ADD'] = [ Opcode Object ... ] }
class OpcodeScraper():
    scraped_opcodes = {}

    def scrape_opcodes(self):      
        response = requests.get(opcode_url, proxies=proxies)
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

    # Returns a Dictionary of lists
    # For example: { ['aritmetic'] = [ list<Opcode Object> ... ] }
    def get_grouped_by_groupname(self):
        grouped_opcodes = {}
        for mnemonic_name, mnemonic_group in self.scraped_opcodes.items():
            group_name = mnemonic_group[0].get_target_group()
            if(group_name not in grouped_opcodes):
                grouped_opcodes[group_name] = []
            grouped_opcodes[group_name].append(mnemonic_group)
        return grouped_opcodes


class Opcode:
    length = 0
    cycles = 0
    flags = ''
    opcode = 0x00
    mnemonic = ''
    mnemonic_complete = ''
    param1 = ''
    param2 = ''

    def __init__(self, x, y, table_content):
        self.opcode = (x << 4) | y

        mnemonic = table_content.contents[0].split(' ')[0].strip()
        splitted_params = table_content.contents[0].replace(mnemonic, '').split(',')

        self.mnemonic_complete = table_content.contents[0]
        self.mnemonic = mnemonic
        self.param1 = splitted_params[0].strip()
        if(len(splitted_params) > 1): self.param2 = splitted_params[1].strip()

        splitted_info = table_content.contents[2].string.split()
        self.length = splitted_info[0].strip()
        self.cycles = splitted_info[1].strip()
        self.flags = table_content.contents[4].string

    def get_opcode_as_string(self, prefix):
        return_value = "{0:0{1}x}".format(self.opcode,2)
        if(prefix): return_value = "{0:#0{1}x}".format(self.opcode,4)
        return return_value

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
            'RES': 'prefix', 'BIT': 'prefix', 'SET': 'prefix',
            'RL': 'prefix', 'RLC': 'prefix', 'RR': 'prefix',
            'RRC': 'prefix', 'SLA': 'prefix', 'SRA': 'prefix',
            'SRL': 'prefix', 'SWAP': 'prefix',
        }
        return switcher.get(self.mnemonic, 'undefined')  

    def display(self):
        display_string = self.get_opcode_as_string(True)
        display_string += ' (' + str(self.length) + ')'
        display_string += ': ' + self.mnemonic + ' ' + self.param1
        if(self.param2 != ''): display_string += ', ' + self.param2
        return display_string 


class LoadedTemplate:
    template_path = ''
    template = None

    def __init__(self, template_path):
        self.template_path = template_path
        filein = open(template_path)
        self.template = Template(filein.read())
        filein.close()

    def write_substitution(self, template_data, output_file):
        substitution = self.get_substitution(template_data)

        if not os.path.exists(os.path.dirname(output_file)):
            os.makedirs(os.path.dirname(output_file))

        output = open(output_file, 'w+')
        output.write(substitution)
        output.close()

    def get_substitutions(self, template_datas):
        output = ''
        for template_data in template_datas:
            output += self.template.substitute(template_data)
        return output

    def get_substitution(self, template_data):
        return self.template.substitute(template_data)


tmpl_instruction_set = LoadedTemplate('templates/instruction_set.template') 
tmpl_instruction_set_item = LoadedTemplate('templates/instruction_set_item.template')
tmpl_group_header = LoadedTemplate('templates/group_header.template')
tmpl_group_header_class = LoadedTemplate('templates/group_header_class.template')
tmpl_group_header_class_item = LoadedTemplate('templates/group_header_class_item.template')
tmpl_group_class = LoadedTemplate('templates/group_class.template')
tmpl_group_class_item = LoadedTemplate('templates/group_class_item.template')


scraper = OpcodeScraper()
scraper.scrape_opcodes()
grouped_by_groupname = scraper.get_grouped_by_groupname()

if not os.path.exists('output'):
    os.makedirs('output')

prefix_items = []
instruction_items = []
for group_name, opcode_groups in grouped_by_groupname.items():
    if(group_name == 'undefined'):
        print('Undefined: ' + opcode_groups[0][0].display())
        continue
    group_class_items = ''
    group_class_definitions = ''
    for opcode_group in opcode_groups:
        group_items = []
        for opcode in opcode_group:
            # If this is a prefix opcode, add it to another list
            list_to_append = []
            set_name = 'set'
            if(group_name == 'prefix'):
                list_to_append = prefix_items
                set_name = 'prefixSet'
            else:
                list_to_append = instruction_items

            list_to_append.append(
                {'set_name': set_name, 'opcode': opcode.get_opcode_as_string(True), 
                'length': opcode.length, 'mnemonic_complete': opcode.mnemonic_complete, 
                'opcode_noprefix': opcode.get_opcode_as_string(False).upper(), 'mnemonic_title': opcode.mnemonic.title() })
            group_items.append({
                'opcode_noprefix': opcode.get_opcode_as_string(False).upper(), 'mnemonic_complete': opcode.mnemonic_complete,
                'mnemonic_title': opcode.mnemonic.title(), 'cycles': opcode.cycles, 'length': opcode.length, 'flags': opcode.flags
            })
        group_class_items += tmpl_group_class_item.get_substitutions(group_items)
        group_class_definitions += tmpl_group_header_class.get_substitution({ 
            'group_class_items': tmpl_group_header_class_item.get_substitutions(group_items),
            'mnemonic_title': opcode.mnemonic.title() 
        })

    tmpl_group_class.write_substitution(
        {'group_class_items': group_class_items, 'group_name': group_name },
        'output/groups/' + group_name + '.cpp')      
    tmpl_group_header.write_substitution(
        {'group_class_definitions': group_class_definitions, 'group_name_upper': group_name.upper() },
        'output/groups/' + group_name + '.hpp')  

tmpl_instruction_set.write_substitution(
    {'instruction_items': tmpl_instruction_set_item.get_substitutions(instruction_items),
     'prefix_items': tmpl_instruction_set_item.get_substitutions(prefix_items) },
    'output/instruction_set.hpp'
)