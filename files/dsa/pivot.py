'''
In this code snippet, I try to come up 
with a way to perform Quicksort's pivot
operation in-place without consulting
any references or tried-and-true implementations.
The runtime seems to be very slow when the list
size approaches 10,000. There's certainly a better
way to do this, but for now I thought I'd showcase
my thought process, even if the results are mediocre.
'''

import random

def check_function(nums, pivot):
    i, j = pivot, pivot
    while i > 0:
        if nums[i] > nums[pivot]:
            return -1
        i -= 1

    while j < len(nums):
        if nums[j] < nums[pivot]:
            return -1
        j += 1

    return 0

def pivot(nums):
    empty = random.randint(0, len(nums)-1)
    pivot = nums[empty]

    flag = 0
    i = 0

    num_operations = 0

    while True:
        num_operations += 1

        if nums[i] < pivot and i > empty:
            nums[empty] = nums[i]
            empty = i
            flag = 1
        elif nums[i] > pivot and i < empty:
            nums[empty] = nums[i]
            empty = i
            flag = 1
        
        i += 1 
        if i >= len(nums):
            if flag == 0:
                break
            flag = 0
            i = 0

    nums[empty] = pivot
    return (empty, num_operations)

def main():
    iterations = 100
    avg_operations = 0
    size = 1000
    for i in range(iterations):
        nums = []
        for _ in range(size):
            nums.append(random.randint(0, 1000))

        result = pivot(nums)
        avg_operations += result[1]

        if check_function(nums, result[0]) != 0:
            print(f"Error: pivot function failed! Aborting...")
            return -1

        print(f"Successful pivots out of {iterations} iterations: {i+1}")

    print(f"Average operations for {iterations} iterations: {avg_operations//iterations}")

if __name__ == "__main__":
    main()
