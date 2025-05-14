#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>


// dados das frequências de letras fornecidos pelo link da atividade.
const float freq_port[26] = { 14.63, 1.04, 3.88, 4.99, 12.57, 1.02, 1.30, 1.28, 6.18, 0.40, 0.02, 2.78, 4.74, 5.05, 10.73, 2.52, 1.20, 6.53, 7.81, 4.34, 4.63, 1.67, 0.01, 0.21, 0.01, 0.47
};

const float freq_ing[26] = { 8.167, 1.492, 2.782, 4.253, 12.702, 2.228, 2.015, 6.094, 6.966, 0.153, 0.772, 4.025, 2.406, 6.749, 7.507, 1.929, 0.095, 5.987, 6.327, 9.056, 2.758, 0.978, 2.360, 0.150, 1.974, 0.074
};


void calculoFreq (const char *texto,  int *totalLetras, float freq[26]) {
    int contador[26] = {0};
    *totalLetras = 0;

    // conta quantas vezes a letra aparece e quarda em um vetor na sua devida posição no alfabeto
    for (int i = 0; texto[i] != '\0'; i++) {
        char letra = tolower(texto[i]);
        if (letra >= 'a' && letra <= 'z') {
            contador[letra - 'a']++;
            (*totalLetras)++;
        }
    }

    // calcula a frequência de cada letra com base no total
    if (*totalLetras > 0) {
        for (int i = 0; i < 26; i++) {
            freq[i] = (contador[i]*100.f)/ *totalLetras;
        }
    }

}

float definirIdioma (const char *texto) {
    float diff_port_total = 0.0;
    float diff_ing_total = 0.0;
    int totalLetras;
    float freq[26];

    // faz primeiro uma verificação de acentos nas letras do texto, ignora o 'é' pq algumas palavras em ingles derivados do francês podem usar.
    const char *letrasAcen = "áâãçêíóôõú";
    for (int i = 0; texto[i] != '\0'; i++) {
        // Verifica se o caractere atual está na lista de caracteres
        if (strchr(letrasAcen, texto[i]) != NULL) {
            printf("O texto provavelmente esta em portugues\n");
            return 1;
        }
    }

    calculoFreq(texto, &totalLetras, freq);

    // calcula o valor absoluto da diferença das frequências
    for (int i = 0; i < 26; i++) {
        diff_port_total += fabs(freq[i] - freq_port[i]);
        diff_ing_total += fabs(freq[i] - freq_ing[i]);
    }

    // usa essa diferença para definir a resposta
    if (diff_port_total < diff_ing_total) {
        printf("O texto provavelmente esta em portugues\n");
    } else {
        printf("O texto provavelmente esta em ingles\n");
    }
}

int main() {
    char texto[1000];

    printf("Digite uma frase ou texto: \n");
    fgets(texto, sizeof(texto), stdin);
    definirIdioma(texto);
    return 0;
}
