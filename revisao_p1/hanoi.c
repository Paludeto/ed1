/*
void hanoiTower(int n, Pilha *inicial, Pilha *auxiliar, Pilha *destino) {

    // Caso base
    if (n == 0) {
        return;
    }

    // Mover n - 1 discos para a pilha auxiliar utilizando a pilha de destino como auxiliar
    hanoiTower(n - 1, inicial, destino, auxiliar);

    // Mover disco maior para a pilha de destino
    push(destino, pop(inicial));

    // Mover n - 1 discos da pilha auxiliar para a pilha de destino utilizando a pilha inicial como auxiliar
    hanoiTower(n - 1, auxiliar, inicial, destino);

}
*/