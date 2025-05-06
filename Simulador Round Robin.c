#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

// ======== Definições e estruturas ========

typedef enum {
    PRONTO,
    EM_EXECUCAO,
    BLOQUEADO,
    CONCLUIDO
} ProcessState;

typedef struct Process {
    int id;
    int time_remaining;
    ProcessState state;
    struct Process* next;
} Process;

Process* process_list = NULL;
int next_process_id = 1;

// ======== Assinaturas de funções ========

void terminal_initialize(void);
void terminal_writestring(const char* str);
void create_process(void);
void list_processes(void);
void terminate_process(int id);
void execute_processes_round_robin(int quantum);

// ======== Função principal ========

int main(void) {
    int opcao;
    int quantum;

    terminal_initialize();

    while (1) {
        terminal_writestring("\nKernel Simples\n");
        terminal_writestring("1. Executar Processos (Round Robin)\n");
        terminal_writestring("2. Criar Processo\n");
        terminal_writestring("3. Listar Processos\n");
        terminal_writestring("4. Terminar Processo\n");
        terminal_writestring("5. Sair\n");
        terminal_writestring("Escolha uma opção: ");

        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                terminal_writestring("Digite o quantum de tempo: ");
                if (scanf("%d", &quantum) == 1) {
                    execute_processes_round_robin(quantum);
                }
                break;
            case 2:
                create_process();
                break;
            case 3:
                list_processes();
                break;
            case 4: {
                terminal_writestring("Digite o ID do processo a ser terminado: ");
                int id;
                if (scanf("%d", &id) == 1) {
                    terminate_process(id);
                }
                break;
            }
            case 5:
                terminal_writestring("Sistema finalizado.\n");
                exit(0);
            default:
                terminal_writestring("Opção inválida!\n");
        }

        sleep(1);
    }

    return 0;
}

// ======== Função de escalonamento Round Robin ========

void execute_processes_round_robin(int quantum) {
    if (!process_list) {
        terminal_writestring("Nenhum processo foi encontrado!\n");
        return;
    }

    terminal_writestring("Iniciando escalonador...\n");
    printf("Quantum definido: %d\n", quantum);

    int current_time = 0;
    int processos_restantes = 0;
    Process* current = process_list;

    while (current) {
        processos_restantes++;
        current = current->next;
    }

    current = process_list;

    while (processos_restantes > 0) {
        if (!current) {
            current = process_list;
            continue;
        }

        if (current->time_remaining <= 0) {
            current = current->next;
            continue;
        }

        current->state = EM_EXECUCAO;
        printf("Tempo %d: Processo %d em execução\n", current_time, current->id);

        int tempo_executado = 0;
        while (tempo_executado < quantum && current->time_remaining > 0) {
            sleep(1);
            current_time++;
            current->time_remaining--;
            tempo_executado++;
            printf("Tempo %d: Processo %d - Tempo restante: %d\n",
                   current_time, current->id, current->time_remaining);
        }

        if (current->time_remaining <= 0) {
            current->state = CONCLUIDO;
            printf("Tempo %d: Processo %d concluído\n", current_time, current->id);
            processos_restantes--;
        } else {
            current->state = PRONTO;
            printf("Tempo %d: Processo %d voltando para estado PRONTO\n",
                   current_time, current->id);
        }

        current = current->next;
    }

    while (process_list) {
        Process* temp = process_list;
        process_list = process_list->next;
        free(temp);
    }

    terminal_writestring("Todos os processos foram executados\n");
}

// ======== Criação de processo ========

void create_process(void) {
    Process* new_process = (Process*)malloc(sizeof(Process));

    if (!new_process) {
        terminal_writestring("Erro: Falha ao criar processo\n");
        return;
    }

    new_process->id = next_process_id++;
    new_process->time_remaining = rand() % 10 + 1;
    new_process->state = PRONTO;
    new_process->next = NULL;

    if (!process_list) {
        process_list = new_process;
    } else {
        Process* temp = process_list;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = new_process;
    }

    terminal_writestring("Processo criado com sucesso\n");
}

// ======== Inicialização do terminal ========

void terminal_initialize(void) {
    terminal_writestring("Inicializando terminal...\n");
}

// ======== Listagem de processos ========

void list_processes(void) {
    Process* current = process_list;
    if (!current) {
        terminal_writestring("Nenhum processo ativo.\n");
        return;
    }

    terminal_writestring("Lista de processos:\n");
    while (current) {
        printf("ID: %d | Estado: %s | Tempo Restante: %d\n",
               current->id,
               (current->state == PRONTO) ? "PRONTO" :
               (current->state == EM_EXECUCAO) ? "EM_EXECUÇÃO" :
               (current->state == BLOQUEADO) ? "BLOQUEADO" :
               "CONCLUÍDO",
               current->time_remaining);
        current = current->next;
    }
}

// ======== Finalização de processo ========

void terminate_process(int id) {
    Process* current = process_list;
    Process* prev = NULL;

    while (current) {
        if (current->id == id) {
            if (prev) {
                prev->next = current->next;
            } else {
                process_list = current->next;
            }
            free(current);
            terminal_writestring("Processo terminado com sucesso!\n");
            return;
        }
        prev = current;
        current = current->next;
    }

    terminal_writestring("Erro: Processo não encontrado!\n");
}

// ======== Escrita no terminal ========

void terminal_writestring(const char* str) {
    printf("%s", str);
}
