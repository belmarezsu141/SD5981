import os
import sys
import configparser

##################################################################################################
# Input                                                                                          #
##################################################################################################
# Variable which can be modified
START_ADDRESS = 0x10000

# Key word used in conversion
PATTERN_START = "d2s_JTAG__Write"
CAP_TITLE_FILE = "Cap_Jtag_title.txt"

# File extension for CAP/STIL Conversion
FILE_EXTENSION = {"CAP": ".cap"}

##################################################################################################
# Function                                                                                       #
##################################################################################################
def conversion_tool_stil(folder_name, bin_file_name, header_lines, pattern_lines):
    current_file = open(os.path.join(folder_name, bin_file_name), "rb")
    output_file = open(os.path.join(folder_name,
                       bin_file_name.replace(".bin",FILE_EXTENSION[mode])), "w")
    bin_lines = bytearray(current_file.read())

    address_list = []
    register_list = []

    # Conversion of firmware byte array into register_list
    temp_address = START_ADDRESS
    for i in range(0,len(bin_lines),2):
        value = (bin_lines[i+1]<<8)+bin_lines[i]
        address_list.append(temp_address)
        register_list.append(value)
        temp_address = temp_address + 0x2

    # Write Burst_Pattern_title
    for h_line in header_lines:
        if PATTERN_START not in h_line:
            output_file.write(h_line)
        else:
            for add_index, address in enumerate(address_list):
                if address == START_ADDRESS:
                    output_file.write('\t\t"'+PATTERN_START+"_0x"+format(address, 'X')+
                    "_0x"+format(register_list[add_index], 'X')+'";\n')
                else:
                    output_file.write('//\t\t"'+PATTERN_START+"_0x"+format(address, 'X')+
                    "_0x"+format(register_list[add_index], 'X')+'";\n')

    # Loop for all address and value
    for add_index, address in enumerate(address_list):
        current_address_bit = list('{0:018b}'.format(address))[:-1]
        current_register_value = register_list[add_index]
        current_register_bit = list('{0:016b}'.format(current_register_value))
        current_address_bit.reverse()
        current_register_bit.reverse()
        temp_index = 0
        # Loop for template file
        for pattern_line in pattern_lines:
            if "Pattern" in pattern_line:
                if add_index == 0:
                    output_file.write('Pattern "'+PATTERN_START+"_0x"+format(address, 'X')+
                    "_0x"+format(current_register_value, 'X')+'" {\n')
                else:
                    output_file.write('// Pattern "'+PATTERN_START+"_0x"+format(address, 'X')+
                    "_0x"+format(current_register_value, 'X')+'" {\n')
            elif "TS1" in pattern_line:
                if add_index == 0:
                    output_file.write(pattern_line)
                else:
                    output_file.write('//'+pattern_line)
            elif '"JTAG_TDI"=' in pattern_line:
                # 28 is the index of * string for JTAG_TDI"=* in the template
                # index_JTAG_TDI = pattern_line.index('"JTAG_TDI"=') + len('"JTAG_TDI"=')
                if temp_index >= 8 and temp_index <= 23:
                    new_line =  pattern_line[:28]+str(current_register_bit[temp_index-8])+pattern_line[29:]
                elif temp_index >= 24 and temp_index <= 40:
                    new_line =  pattern_line[:28]+str(current_address_bit[temp_index-24])+pattern_line[29:]
                else:
                    new_line = pattern_line
                temp_index = temp_index + 1
                output_file.write(new_line)
            else:
                output_file.write('//'+pattern_line)
        output_file.write('\n')
    output_file.write('}\n')
    output_file.close()

def conversion_tool_cap(folder_name, bin_file_name, template_cap_list):
    current_file = open(os.path.join(folder_name, bin_file_name), "rb")
    output_file = open(os.path.join(folder_name,
                       bin_file_name.replace(".bin",FILE_EXTENSION[mode])), "w")
    bin_lines = bytearray(current_file.read())

    address_list = []
    register_list = []

    # Conversion of firmware byte array into register_list
    temp_address = START_ADDRESS
    for i in range(0,len(bin_lines),2):
        value = (bin_lines[i+1]<<8)+bin_lines[i]
        address_list.append(temp_address)
        register_list.append(value)
        temp_address = temp_address + 0x2

    cap_index = 0
    # Write Cap Template Header
    for i, h_line in enumerate(template_cap_list):
        cap_index = i
        if PATTERN_START in h_line:
            break
        else:
            output_file.write(h_line)

    for add_index, address in enumerate(address_list):
        current_address_bit = list('{0:018b}'.format(address))[:-1]
        current_register_value = register_list[add_index]
        current_register_bit = list('{0:016b}'.format(current_register_value))
        # Endianesss
        current_address_bit.reverse()
        current_register_bit.reverse()
        output_file.write("\t// "+PATTERN_START+"_0x"+format(address, 'X')+
                          "_0x"+format(register_list[add_index], 'X')+"\n")
        for temp_index, timeplate_list in enumerate(template_cap_list[cap_index+1:-1]):
            if temp_index >= 7 and temp_index <= 22:
                new_line =  timeplate_list[:33]+str(current_register_bit[temp_index-7])+timeplate_list[34:] 
            elif temp_index >= 23 and temp_index <= 39:
                new_line =  timeplate_list[:33]+str(current_address_bit[temp_index-23])+timeplate_list[34:] 
            else:
                new_line = timeplate_list
            output_file.write(new_line)
    output_file.write('}\n')
    output_file.close()

##################################################################################################
# Main                                                                                           #
##################################################################################################
if __name__ == "__main__":
    bin_folder = os.path.dirname(os.path.realpath(sys.argv[0]))
    all_file_list = os.listdir(bin_folder)
    bin_file_list = [f for f in all_file_list if f.endswith('.bin')]
    print("Current Folder for bon/template  : "+bin_folder)
    mode = "CAP"

    try:
        # Firmware Files check
        if not bin_file_list:
            raise Exception("Folder Selection Error, .bin file is not found")

        # Template Check and parse

        if not CAP_TITLE_FILE in all_file_list:
            raise Exception("Folder Selection Error, template file is not found")
        cap_template_file = open(os.path.join(bin_folder, CAP_TITLE_FILE), "r")
        cap_template_lines = cap_template_file.readlines()
        cap_template_file.close()
      
        #Main Conversion
        for bin_file in bin_file_list:
            conversion_tool_cap(bin_folder, bin_file, cap_template_lines)         
        print("The conversion is done, please check the folder")

    except Exception as err:
        print(str(err))
    finally:
        input("Please Enter to Exit")