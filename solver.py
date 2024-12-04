import timeit

def bool_to_string(is_correct):
    return "correct" if is_correct else "incorrect"

def default_int_parser(solution_file_name):
    solutions = []
    with open(solution_file_name, 'r') as file:
        for line in file:
            solutions.append(int(line))
    
    return solutions

def test_solvers(solvers, testing_metadatas=None):
    for idx, solver in enumerate(solvers):
        if testing_metadatas:
            solver.report_trial_with_and_without_parsing(testing_metadatas[idx])
            continue
        
        solver.report_trial_with_and_without_parsing()

class Solver:
    def __init__(self, name, day, puzzle, parser, solver, solution_parser=None):
        self.name = f"D{day}P{puzzle} \"{name}\""
        self.day = day
        self.puzzle = puzzle
        self.parser = parser
        self.solver = solver
        
        if solution_parser is None:
            solution_parser = default_int_parser
        self.solution_parser = solution_parser
        self.input_name = f"day{day}/input.txt"
        self.solution_name = f"day{day}/solutions.txt"
        
    def parse_file(self, input_file_name=None):
        if input_file_name is None:
            input_file_name = self.input_name
            
        return self.parser(input_file_name)
    
    def compute_solution(self, data=None, input_file_name=None):
        if data is not None and input_file_name is not None:
            raise ValueError("Data and input file name cannot both be specified.")
        if data is None:
            data = self.parse_file(input_file_name)
            
        return self.solver(data)
    
    def get_correct_solution(self, solution_file_name=None):
        if solution_file_name is None:
            solution_file_name = self.solution_name
            
        return self.solution_parser(solution_file_name)[self.puzzle - 1]
    
    def time_solver(self, num_batches, num_reps, data=None, input_file_name=None):
        if data:
            time = min(timeit.repeat(lambda: self.compute_solution(data), number=num_reps, repeat=num_batches))
        else:
            time = min(timeit.repeat(lambda: self.compute_solution(input_file_name=input_file_name), number=num_reps, repeat=num_batches))

        return round(time / num_reps * 1000000)
            
    def verify_solver(self, data=None, input_file_name=None, solution_file_name=None):
        computed_solution = self.compute_solution(data, input_file_name)
        correct_solution = self.get_correct_solution(solution_file_name)
        
        return (computed_solution == correct_solution, computed_solution, correct_solution)
    
    def report_verification(self, data=None, input_file_name=None, solution_file_name=None):
        is_correct, computed_solution, correct_solution = self.verify_solver(data, input_file_name, solution_file_name)
        if is_correct:
            print(f"✓✓✓ {self.name} got correct solution: {computed_solution}")
            return
        
        print(f"xxx {self.name} got incorrect solution: {computed_solution}. Correct solution is: {correct_solution}")

    def trial(self, num_batches=5, num_reps=1000, data=None, input_file_name=None, solution_file_name=None):
        is_correct = self.verify_solver(data, input_file_name, solution_file_name)[0]
        best_avg = self.time_solver(num_batches, num_reps, data, input_file_name)
        return (is_correct, best_avg)
    
    def report_trial_with_and_without_parsing(self, timing_metadata={"parsing":(10, 100), "no_parsing":(5, 1000)},
                                              input_file_name=None, solution_file_name=None):
        is_correct_parsing, best_avg_parsing = self.trial(timing_metadata["parsing"][0], timing_metadata["parsing"][1], None, input_file_name, solution_file_name)
        data = self.parse_file(input_file_name)
        is_correct_no_parsing, best_avg_no_parsing = self.trial(timing_metadata["no_parsing"][0], timing_metadata["no_parsing"][1], data, input_file_name, solution_file_name)
        
        if is_correct_parsing and is_correct_no_parsing:
            print(f"✓✓✓ {self.name} got correct solution in {best_avg_no_parsing}μs ({best_avg_parsing}μs w/ parsing)")
            return 
        
        print(f"xxx {self.name} was {bool_to_string(is_correct_parsing)} (parsing) and {bool_to_string(is_correct_no_parsing)} (no parsing)")
        
        