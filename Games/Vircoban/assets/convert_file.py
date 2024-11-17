import sys
import struct

def convert_file(input_file_path, output_file_path, maxbytes):
    try:
        # Open the input file in binary read mode
        with open(input_file_path, 'r') as input_file:
            # Open the output file in binary write mode
            with open(output_file_path, 'wb') as output_file:
                content = input_file.read()
                numbytes = 0
                               
                for value in content:
                    # Strip any extra whitespace and convert the value to an integer
                    if value:
                        try:
                            int_value = int(ord(value))                            
                        except ValueError:
                            print(f"Skipping invalid value: {value}")
                            continue# Pack the integer as a 4-byte int32 in little-endian format
                        int32_bytes = struct.pack('<i', int_value)
                        
                        # Write the 4-byte int32 to the output file
                        output_file.write(int32_bytes)
                        numbytes+=1
                #pad with zero        
                for i in range(maxbytes-numbytes):
                    int32_bytes = struct.pack('<i', 0)
                    output_file.write(int32_bytes)
                    

        print("File conversion complete!")
    
    except IOError as e:
        print(f"An error occurred: {e}")

if __name__ == "__main__":
    if len(sys.argv) != 4:
        print("Usage: python convert_file.py <input_file> <output_file> <max_bytes>")
    else:
        input_file_path = sys.argv[1]
        output_file_path = sys.argv[2]
        maxbytes = int(sys.argv[3])
        convert_file(input_file_path, output_file_path, maxbytes)