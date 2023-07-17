import matplotlib.pyplot as plt
import numpy as np

def read_data_file(filename):
    with open(filename, 'r') as file:
        cases = []
        while True:
            case = {}
            test_case = file.readline().strip()
            if not test_case:
                break
            case['test_case'] = int(test_case)
            case['total_points'] = int(file.readline().strip())
            case['coordinates'] = []
            for _ in range(case['total_points']):
                x, y = map(int, file.readline().split())
                case['coordinates'].append((x, y))
            file.readline()
            cases.append(case)
        return cases

def read_results_file(filename):
    with open(filename, 'r') as file:
        results = []
        while True:
            result = {}
            test_case = file.readline().strip()
            if not test_case:
                break
            result['test_case'] = int(test_case)
            result['model'] = list(map(float, file.readline()[1:-2].split(',')))
            result['fit'] = float(file.readline().strip())
            result['inliers'] = int(file.readline().strip())
            result['angle'] = float(file.readline().strip())
            result['distance'] = float(file.readline().strip())
            results.append(result)
            file.readline()
        return results


def plot_cases(cases, results):
    num_cases = len(cases)

    # Calcular o tamanho da grade de subplots
    ncols = int(np.ceil(np.sqrt(num_cases)))
    nrows = int(np.ceil(num_cases / ncols))

    # Criar a grade de subplots
    fig, axs = plt.subplots(nrows=nrows, ncols=ncols, figsize=(12, 8))
    fig.tight_layout(pad=3.0)

    # Iterar sobre os casos de teste
    for i, case in enumerate(cases):
        
        
        # Extrair coordenadas x e y dos pontos
        x_coords, y_coords = zip(*case['coordinates'])

        # Obter o resultado correspondente ao caso de teste
        result = results[i]
        print(case['total_points'], result['inliers'])

        # Criar array de pontos para a linha do modelo
        x_model = np.array([min(x_coords), max(x_coords)])
        y_model = np.polyval(result['model'], x_model)

        # Calcular índices para o subplot atual
        row = i // ncols
        col = i % ncols

        # Plotar os pontos e a linha do modelo no subplot atual
        axs[row, col].scatter(x_coords, y_coords, color='blue', label='Pontos')
        axs[row, col].plot(x_model, y_model, color='red', label='Modelo')
        axs[row, col].axvline(x=result['distance'], color='green', linestyle='--', label='Distância')
        axs[row, col].set_xlabel('Coordenada X')
        axs[row, col].set_ylabel('Coordenada Y')
        axs[row, col].set_title(f'Caso de Teste {case["test_case"]}')
        axs[row, col].legend()
        axs[row, col].grid(True)

        # Ajustar os limites dos eixos
        axs[row, col].set_xlim(0, 50)
        axs[row, col].set_ylim(50, 0)

    # Remover subplots vazios, se houver
    for i in range(num_cases, nrows * ncols):
        row = i // ncols
        col = i % ncols
        fig.delaxes(axs[row, col])

    plt.show()


data_cases = read_data_file('resultados\\FPGAin.txt')
results = read_results_file('resultados\\FPGAout.txt')
print(data_cases)
plot_cases(data_cases, results)