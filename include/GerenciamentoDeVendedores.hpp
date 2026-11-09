#ifndef GERENCIAMENTODEVENDEDORES_HPP
#define GERENCIAMENTODEVENDEDORES_HPP
#include <vector>
#include <deque>
#include "Vendedor.hpp"
#include "Venda.hpp"

    /** 
    *@brief GerenciamentoDeVendedores é uma classe que gerencia os vendedores cadastrados no sistema. Ela possui métodos para validar o email e o CPF dos vendedores, além de permitir a alteração do nome de um vendedor.
    */

    class GerenciamentoDeVendedores {
        private:
        std::deque<Vendedor> vendedores;
        std::vector<Venda> vendas;

      public:
    void adicionarVendedor(const Vendedor& vendedor);
    void adicionarVenda(const Venda& venda);
    bool clientePossuiVendas(const std::string& cpf) const;
    bool possuiVendas() const;
    
    Vendedor* buscarVendedor(const std::string& id);
        /**
         * @brief mostrarVendedores imprime uma lista com todos os vendedores ativos
         */
            void mostrarVendedores();
        /**
         * @brief mostrarDadosVendas imprime uma lista com varios dados sobre as vendas
         */
            void mostrarDadosVendas();
        /**
         * @brief filtrarDados aplica uma configuração sobre os dados a serem exibidos
        */
            void filtraDados();
        };

    #endif