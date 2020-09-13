#ifndef _CORE_DB_DATABASE_STRATEGY_HPP
#define _CORE_DB_DATABASE_STRATEGY_HPP

#include <sqlite/connection.hpp>

/**
 * @interface DatabaseStrategy
 * 
 * Implementa o padrão de projeto Strategy para executar algoritmos de interação
 * com o banco de dados que podem ser diferentes para cada problema abordado
 */
class DatabaseStrategy {
public:
  typedef sqlite::connection Connection;

  virtual ~DatabaseStrategy() {};

  /**
   * Criar uma tabela no arquivo de banco de dados definido pelo objeto de conexão
   * @param con ponteiro para um sqlite::connection (a conexão aberta com arquivo sqlite) */
  virtual void create_table(Connection *con) = 0;

  /**
   * Inserir dados em uma instância de banco de dados
   * @param con ponteiro para um sqlite::connection (a conexão aberta com arquivo sqlite) */
  virtual void insert_data(Connection *con) = 0;
};

#endif