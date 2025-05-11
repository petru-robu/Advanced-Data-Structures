import random

def generate_test(p1:int, p2:int, p3:int, num_queries:int = 100_000, max_val:int =100_000, filename: str = "test.in"):
    if p1 + p2 + p3 != 100:
        raise ValueError("Percentages must add up to 100!")

    num_type1 = int(p1 / 100 * num_queries)
    num_type2 = int(p2 / 100 * num_queries)
    num_type3456 = num_queries - num_type1 - num_type2

    with open(filename, "w") as f:
        f.write(str(num_queries) + "\n")

        query_counts = {1: 0, 2: 0, 3: 0, 4: 0, 5: 0, 6: 0}  

        for _ in range(num_queries):
            query_type = 0
            rand_val = random.randint(1, 100)

            if rand_val <= p1 and query_counts[1] < num_type1:
                query_type = 1
                query_counts[1] += 1
            elif rand_val <= p1 + p2 and query_counts[2] < num_type2:
                query_type = 2
                query_counts[2] += 1
            elif query_counts[3] + query_counts[4] + query_counts[5] + query_counts[6] < num_type3456:
                query_type = random.randint(3, 6)
                query_counts[query_type] += 1
            else:
                remaining_types = [t for t in range(1, 7) if query_counts[t] < 
                                   (num_type1 if t == 1 else num_type2 if t == 2 
                                    else num_type3456 / 4 if t >= 3 else 0)]
                if remaining_types:
                    query_type = random.choice(remaining_types)
                    query_counts[query_type] += 1
                else:
                    break

            if query_type in [1, 2, 3, 4, 5]:
                x = random.randint(-max_val, max_val)
                f.write(f"{query_type} {x}\n")\
                
            elif query_type == 6:
                x = random.randint(-max_val, max_val)
                y = random.randint(-max_val, max_val)
                if x > y:
                    x, y = y, x
                f.write(f"{query_type} {x} {y}\n")
        
        #print(query_counts)


def generator():
    #tests with insertions and few searches
    for i in range(3):
        path = "./tests/insertion_heavy" + str(i) + '.in'
        print(path)

        generate_test(80, 10, 10, num_queries=100_000, filename=path)
    
    #tests with insertions and deletions
    for i in range(3):
        path = "./tests/insert_remove_heavy" + str(i) + '.in'
        print(path)

        generate_test(45, 45, 10, num_queries=100_000, filename=path)

    #tests with few insertions and a lot of searches
    for i in range(3):
        path = "./tests/search_heavy" + str(i) + '.in'
        print(path)

        generate_test(15, 5, 80, num_queries=100_000, filename=path)

    #average tests
    for i in range(3):
        path = "./tests/average" + str(i) + '.in'
        print(path)

        generate_test(25, 25, 50, num_queries=100_000, filename=path)



if __name__ == "__main__":
    generator()