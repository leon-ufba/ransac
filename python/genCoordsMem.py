def generate_mif(input_file, output_file):
    with open(input_file, 'r') as file:
        lines = file.readlines()

    content = "DEPTH={};".format(len(lines) * 2)
    content += "\nWIDTH=32;\n\nADDRESS_RADIX=UNS;\nDATA_RADIX=UNS;\n\nCONTENT BEGIN\n"

    for i, line in enumerate(lines):
        numbers = line.strip().split()
        if len(numbers) != 2:
            print("Erro: Cada linha do arquivo deve conter dois números.")
            return


        content += "    {} : {};\n".format(i * 2, numbers[0])
        content += "    {} : {};\n".format(i * 2 + 1, numbers[1])

    content += "END;"

    with open(output_file, 'w') as file:
        file.write(content)

    print("Arquivo MIF gerado com sucesso!")


# Exemplo de uso
input_file = 'coords/data0.txt'
output_file = 'coords/memoria.mif'

generate_mif(input_file, output_file)