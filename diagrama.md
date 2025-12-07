@startuml

class Veiculo {

- string tipo
- string marca
- string model
- string cor
- float diaria
- bool disponivel

* Veiculo()
* Veiculo(string tipo, string marca, string model, string cor, float diaria, bool disponivel)
* getTipo(): string
* getMarca(): string
* getModel(): string
* getCor(): string
* getDiaria(): float
* isDisponivel(): bool
* setDisponivel(bool status): void
* infoVeiculos(): void <<virtual>>
  }

class Carro {

- Carro()
- Carro(string tipo, string marca, string model, string cor, float diaria, bool disponivel)
- lerLista(nomeArquivo: string): vector<Carro\*> <<static>>
- imprimirLista(lista: vector<Carro\*>): void <<static>>
- infoVeiculos(): void
  }

class Moto {

- Moto()
- Moto(string tipo, string marca, string model, string cor, float diaria, bool disponivel)
- lerLista(nomeArquivo: string): vector<Moto\*>
- imprimirLista(lista: vector<Moto\*>): void
- infoVeiculos(): void <<override>>
  }

class Cliente {

- string nome
- string cpf
- Veiculo\* veiculoEscolhido

* Cliente()
* Cliente(const string& nome, const string& cpf)
* getNome(): string
* getCpf(): string
* setVeiculoEscolhido(): void
* setVeiculoEscolhido(Veiculo\* v): void
* getVeiculoEscolhido(): Veiculo\*
* infoCliente(): void <<const>>
  }

class Contrato {

- string dataRetirada
- int diasAluguel
- bool seguro
- float valorFinal
- Cliente cliente
- Veiculo\* veiculo

* Contrato(const Cliente& c, Veiculo\* v)
* preencherFormulario(): void
* calcularValorFinal(): void
* gerarArquivoTxt(nomeArquivo: string): void <<const>>
  }

Veiculo <|-- Carro
Veiculo <|-- Moto
Cliente --> Veiculo
Contrato --> Cliente
Contrato --> Veiculo

@enduml
