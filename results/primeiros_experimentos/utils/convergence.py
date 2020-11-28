class Convergence:
    raw: str

    def __init__(self, raw_data):
        self.raw = raw_data


    def parse(self, sep, dtype=float) -> list:
        return [ dtype(val) for val in self.raw.split(sep) ]


