# ⚙️ Simulador de Escalonamento Round Robin em C

Este é um projeto de simulação de **escalonamento de processos** utilizando o algoritmo **Round Robin**, desenvolvido em **linguagem C**, com foco educacional em sistemas operacionais e gerenciamento de processos.

## 🚀 Como Executar

1. Certifique-se de ter um compilador C instalado.
2. Compile o arquivo.
3. Execute o programa.

## 🔄 Funcionalidades

- ✅ Criar processos com tempo de execução aleatório
- ✅ Executar processos com o algoritmo **Round Robin**
- ✅ Listar processos com seus respectivos estados e tempos restantes
- ✅ Encerrar manualmente qualquer processo da fila

## 🧠 Estados dos Processos

- `PRONTO`: processo criado, aguardando execução
- `EM_EXECUCAO`: processo em uso da CPU
- `CONCLUIDO`: processo finalizado (é removido da fila)
- `BLOQUEADO`: estado reservado para futuras extensões

## 🛠 Tecnologias

- **C padrão ANSI**
- Manipulação de ponteiros e listas encadeadas
- Simulação com `sleep()` para controle de tempo

---
#### Desenvolvido por Cícero Braule ✨
