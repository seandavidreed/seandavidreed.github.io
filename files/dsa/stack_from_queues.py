# January 17, 2024

class Queue:
    def __init__(self, size):
        self.head = 0
        self.tail = 0
        self.size = size
        self.array = [None] * size

    def is_full(self):
        if self.head == self.tail + 1:
            return True
        return False

    def is_empty(self):
        if self.head == self.tail:
            return True
        return False

    def enqueue(self, element):
        if self.is_full():
            raise IndexError

        self.array[self.tail] = element
        self.tail += 1

        if self.tail == self.size:
            self.tail = 0

    def dequeue(self):
        if self.is_empty():
            raise IndexError

        x = self.array[self.head]

        if self.head == self.size - 1:
            self.head = 0
        else:
            self.head += 1

        return x

    def printf(self):
        if self.is_empty():
            return
        elif self.tail > self.head:
            print(self.array[self.head:self.tail])
        else:
            print(self.array[self.head:] + self.array[:self.tail])

    def print(self):
        print(self.array)

class Stack:
    def __init__(self, size):
        size = size // 2
        self.state = 0
        self.queue0 = Queue(size+1)
        self.queue1 = Queue(size+1)

    def is_full(self):
        if self.queue0.is_full() or self.queue1.is_full():
            return True
        return False

    def is_empty(self):
        if self.queue0.is_empty() and self.queue1.is_empty():
            return True
        return False

    def push(self, element):
        if self.is_full():
            raise IndexError

        if self.queue0.is_empty():
            self.queue1.enqueue(element)
        else:
            self.queue0.enqueue(element)

        return element

    def pop(self):
        if self.is_empty():
            raise IndexError

        if self.queue0.is_empty():
            while True:
                x = self.queue1.dequeue()
                if self.queue1.is_empty():
                    break
                self.queue0.enqueue(x)
        else:
            while True:
                x = self.queue0.dequeue()
                if self.queue0.is_empty():
                    break
                self.queue1.enqueue(x)
        return x

    def printf(self):
        self.queue0.printf()
        self.queue1.printf()


def main():
    stack = Stack(size=100)

    stack.printf()

    print(f'Push -> {stack.push(9)}')
    print(f'Push -> {stack.push(8)}')
    print(f'Push -> {stack.push(7)}')
    print(f'Push -> {stack.push(6)}')
    print(f'Push -> {stack.push(5)}')
    print(f'Push -> {stack.push(4)}')
    print(f'Push -> {stack.push(3)}')

    stack.printf()

    print(f'Pop -> {stack.pop()}')

    print(f'Push -> {stack.push("z")}')
    print(f'Push -> {stack.push("y")}')

    stack.printf()

    print(f'Pop -> {stack.pop()}')
    print(f'Pop -> {stack.pop()}')
    print(f'Pop -> {stack.pop()}')
    print(f'Pop -> {stack.pop()}')
    print(f'Pop -> {stack.pop()}')
    print(f'Pop -> {stack.pop()}')
    print(f'Pop -> {stack.pop()}')

    stack.printf()

if __name__ == "__main__":
    main()
