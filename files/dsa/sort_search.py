import random
import sys
import os

def quick_sort(nums: list) -> list:
    # Base case. Nothing to do here since lists
    # of size 1 are already sorted (trivially).
    if len(nums) < 2:
        return nums

    # Recursive case. Pick random element and
    # pivot all other elements around it.
    rand_idx = random.randint(0, len(nums) - 1)
    aux = [0] * len(nums)

    i, j, k = -1, 0, len(nums) - 1
    
    for i in range(len(nums)):
        if i == rand_idx:
            continue
        if nums[i] <= nums[rand_idx]:
            aux[j] = nums[i]
            j = j + 1
        else:
            aux[k] = nums[i]
            k = k - 1

    aux[j] = nums[rand_idx]

    nums = list(aux)
    del aux
    nums[:j] = quick_sort(nums[:j])
    nums[j+1:] = quick_sort(nums[j+1:])

    return nums

def binary_search(nums: list, a: int, b: int, find: int) -> int:
    if a > b:
        return -1

    mid = a + (b - a) // 2

    if find < nums[mid]:
        return binary_search(nums, a, mid-1, find)
    elif find > nums[mid]:
        return binary_search(nums, mid+1, b, find)
    else:
        return mid

def main():
    if len(sys.argv) != 2:
        print("Usage: python3 sort_search.py <INTEGER>")
        return -1

    try:
        find = int(sys.argv[1])
    except ValueError:
        print("Usage: python3 sort_search.py <INTEGER>")
        return -1

    nums = []
    for i in range(100000):
        nums.append(random.randint(0, 100000))
    new_nums = quick_sort(nums)
    print(new_nums)

    while True:
        print(f"Searching for {find}")
        result = binary_search(new_nums, 0, len(new_nums)-1, find)
        
        if result == -1:
            print("Not Found")
        else:
            print(f"{find} found at index {result}")

        choice = input(f"Do you want to search again? [y/n]: ")

        if choice.upper() != 'Y':
            return
        while True:
            find = input("Enter new integer: ")
            try:
                find = int(find)
                break
            except ValueError:
                print("Please provide an integer.")

if __name__ == "__main__":
    main()
