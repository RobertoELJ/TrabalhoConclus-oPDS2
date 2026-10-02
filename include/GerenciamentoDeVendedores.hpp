#ifndef GERENCIAMENTODEVENDEDORES_HPP
#define GERENCIAMENTODEVENDEDORES_HPP


    ///GerenciamentoDeVendedores é uma classe que gerencia os vendedores cadastrados no sistema. Ela possui métodos para validar o email e o CPF dos vendedores, além de permitir a alteração do nome de um vendedor.
    class GerenciamentoDeVendedores {
        private:

        public:
            void mostrarVendedores();
            void mostrarDadosVendas();
            void filtraDados();
        };

    #endif