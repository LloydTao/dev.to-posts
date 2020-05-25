#include <stdio.h>

void apple() {
    printf("Apple!\n");
}

void banana() {
    printf("Banana!\n");
}

void cherry() {
    printf("Cherry!\n");
}

void (*pointer_to_apple())() {
    printf("Getting pointer to apple.\n");
    return &apple;
}

void (*pointer_to_banana())() {
    printf("Getting pointer to banana.\n");
    return &banana;
}

void (*pointer_to_cherry())() {
    printf("Getting pointer to cherry.\n");
    return &cherry;
}

int main() {
    void (*(*foo[3])())() = {
            &pointer_to_apple,
            &pointer_to_banana,
            &pointer_to_cherry
    };
    size_t n = sizeof(foo) / sizeof(foo[0]);
    for (int i = 0; i < n; ++i) {
        foo[i]()();
    }
    return 0;
}
