#!/usr/bin/env python
from assimilator import *
from Boinc import boinc_project_path
import os

class PrinesAssimilator(Assimilator):
    def __init__(self):
        Assimilator.__init__(self)
        
    def assimilate_handler(self, wu, results, canonical_result):
        if canonical_result == None:
            return
        out_path = boinc_project_path.project_path("download/results/prines");
        in_path = self.get_file_path(canonical_result)

        with open(in_path) as in_file:
            in_str = in_file.read()

        try:
            os.makedirs(out_path)
        except OSError:
            pass

        with open(os.path.join(out_path, "prines_results.txt"), "a") as out_file:
            out_file.write(in_str)

if __name__ == "__main__":
    asm = PrinesAssimilator()
    asm.run()
