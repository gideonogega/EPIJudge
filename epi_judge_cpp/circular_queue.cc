#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
#include "test_framework/test_failure.h"

class Queue {
public:
    Queue(size_t capacity)
    {
        this->capacity = capacity;
        items = new int[capacity];
    }
    void Enqueue(int x) {
        if (size == capacity)
        {
            int* oldItems = items;
            int newCapacity = capacity * 2;
            items = new int[newCapacity];
            for (int i = 0; i < size; i++)
            {
                items[i] = oldItems[head];
                head++;
                if (head >= capacity) head = 0;
            }
            capacity = newCapacity;
            head = 0;
            tail = size - 1;
        }
        else if (tail == capacity - 1) tail = -1;

        tail++;
        items[tail] = x;
        size++;
    }
    int Dequeue() {
        int item = items[head];
        head++;;
        if (head == capacity) head = 0;
        size--;
        return item;
    }
    int Size() const {
        return size;
    }
private:
    int* items;
    int capacity = 0;
    int head = 0;
    int tail = -1;
    int size = 0;
};
struct QueueOp {
    enum class Operation { kConstruct, kDequeue, kEnqueue, kSize } op;
    int argument;

    QueueOp(const std::string& op_string, int arg) : argument(arg) {
        if (op_string == "Queue") {
            op = Operation::kConstruct;
        }
        else if (op_string == "dequeue") {
            op = Operation::kDequeue;
        }
        else if (op_string == "enqueue") {
            op = Operation::kEnqueue;
        }
        else if (op_string == "size") {
            op = Operation::kSize;
        }
        else {
            throw std::runtime_error("Unsupported queue operation: " + op_string);
        }
    }

    void execute(Queue& q) const {
        switch (op) {
        case Operation::kConstruct:
            // Hack to bypass deleted assign operator
            q.~Queue();
            new (&q) Queue(argument);
            break;
        case Operation::kDequeue: {
            int result = q.Dequeue();
            if (result != argument) {
                throw TestFailure("Dequeue: expected " + std::to_string(argument) +
                    ", got " + std::to_string(result));
            }
        } break;
        case Operation::kEnqueue:
            q.Enqueue(argument);
            break;
        case Operation::kSize: {
            int s = q.Size();
            if (s != argument) {
                throw TestFailure("Size: expected " + std::to_string(argument) +
                    ", got " + std::to_string(s));
            }
        } break;
        }
    }
};

namespace test_framework {
    template <>
    struct SerializationTrait<QueueOp> : UserSerTrait<QueueOp, std::string, int> {};
}  // namespace test_framework

void QueueTester(const std::vector<QueueOp>& ops) {
    Queue q(0);
    for (auto& op : ops) {
        op.execute(q);
    }
}

int main(int argc, char* argv[]) {
    std::vector<std::string> args{ argv + 1, argv + argc };
    std::vector<std::string> param_names{ "ops" };
    return GenericTestMain(args, "circular_queue.cc", "circular_queue.tsv",
        &QueueTester, DefaultComparator{}, param_names);
}
