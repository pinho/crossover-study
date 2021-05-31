from sqlite3 import Connection
from dataclasses import dataclass

class DataSolver:
    @staticmethod
    def resolve_integers_list(convergence: str) -> list[int]:
        return [ int(value) for value in convergence.split(',') ]

    @staticmethod
    def resolve_floats_list(convergence: str) -> list[float]:
        return [ float(value) for value in convergence.split(',') ]

    @staticmethod
    def resolve_crossover_name(crossover_id: int) -> str:
        if crossover_id == 0:
            return 'Uniforme'
        elif crossover_id == 1:
            return 'Um-ponto'
        elif crossover_id > 1:
            return f'{int(crossover_id)}-pontos'
        else:
            raise ValueError('Impossible resolve the name of crossover operator')


@dataclass
class SteinerTreeData:
    """
    DataClass for Steiner tree executions rows in table
    """
    num_steiner_nodes: int
    steiner_nodes: list[int]
    total_costs: int
    convergence: list[int]

    @staticmethod
    def from_table(con: Connection):
        """
        Create a list of Steiner tree rows objects from a table in database file
        """
        data = []
        cur = con.cursor()
        
        for tup in cur.execute(
                '''SELECT num_steiner_nodes, steiner_nodes, total_costs, convergence 
                FROM steiner_executions'''):
            nodes =  DataSolver.resolve_integers_list(tup[1])
            convergence = DataSolver.resolve_integers_list(tup[3])
            s = SteinerTreeData(tup[0], nodes, tup[2], convergence)
            data.append(s)
            pass

        cur.close()
        return data


def resolve_convergence(convergence: str) -> list[int]:
    return DataSolver.resolve_integers_list(convergence)

