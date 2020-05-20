"""@package output_format

Pacote voltado para formatação de strings de saída no console para as execuções
"""
import os

class UnixColor:
    """classe para definição de cores
    """

    unix_prefix = '\e[38;5;'
    RESET = '\e[0m'

    def __init__(self, code: int, prefix = unix_prefix):
        """Construtor

        Recebe um código e opicionalmente um prefixo, que define o código de cor
        no terminal unix. Exemplo:
        >>> UnixColor(9)
        "\e[38;5;9m"

        >>> UnixColor(32, prefix=r"\033[")
        "\033[32m"
        """
        self.code = code
        self.prefix = prefix


    def __str__(self):
        """Retorna a string correpondente do código de cor unix
        """
        return f"{self.prefix}{self.code}m"


    def echo(self, text: str):
        os.system(f'echo -e \"{self}{text}{self.RESET}\"')

    
