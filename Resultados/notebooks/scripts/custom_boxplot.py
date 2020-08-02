"""
Customização de gráficos boxplot
"""

# Definições de componentes de gráficos bem como linhas, pontos, etc...
red_square = dict(markerfacecolor='r', marker='s')
red_circle = dict(makerfacecolor='r', marker='o')
red_diamond = dict(markerfacecolor='r', marker='D', markeredgecolor='white')
black_diamond = dict(markerfacecolor='black', marker='D', markeredgecolor='white')
black_box = dict(linestyle='-', color='white', facecolor='black')


def custom_boxplot(bp_dict):
    # Estilizando as linhas
    for line in bp_dict["whiskers"]:
        line.set_color("#000")
