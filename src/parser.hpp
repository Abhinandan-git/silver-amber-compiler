#pragma once

#include "arena.hpp"
#include "tokenization.hpp"

struct NodeTermIntegerLiteral {
	Token integer_literal;
};
struct NodeTermIdentifier {
	Token identifier;
};
struct NodeExpression;
struct NodeBinaryExpressionAddition {
	NodeExpression *lhs;
	NodeExpression *rhs;
};
// struct NodeBinaryExpressionMultiplication {
// 	NodeExpression *lhs;
// 	NodeExpression *rhs;
// };
struct NodeBinaryExpression {
	// std::variant<NodeBinaryExpressionAddition *, NodeBinaryExpressionMultiplication *> var;
	NodeBinaryExpressionAddition* add;
};
struct NodeTerm {
	std::variant<NodeTermIntegerLiteral *, NodeTermIdentifier *> var;
};
struct NodeExpression {
	std::variant<NodeTerm *, NodeBinaryExpression *> var;
};
struct NodeStatementExit {
	NodeExpression *expression;
};
struct NodeStatementVariable {
	Token identifier;
	NodeExpression *expression;
};
struct NodeStatement {
	std::variant<NodeStatementExit *, NodeStatementVariable *> var;
};
struct NodeProgram {
	std::vector<NodeStatement *> statements;
};

class Parser {
public:
	inline explicit Parser(std::vector<Token> tokens) : m_tokens(std::move(tokens)), m_allocator(1024 * 1024 * 4) {}

	inline std::optional<NodeTerm *> parse_term() {
		if (auto integer_literal = try_consume(TokenType::t_integer_literal)) {
			auto node_term_integer_literal = m_allocator.allocate<NodeTermIntegerLiteral>();
			node_term_integer_literal->integer_literal = integer_literal.value();
			auto node_term = m_allocator.allocate<NodeTerm>();
			node_term->var = node_term_integer_literal;
			return node_term;
		} else if (auto identifier = try_consume(TokenType::t_identifier)) {
			auto node_term_identifier = m_allocator.allocate<NodeTermIdentifier>();
			node_term_identifier->identifier = identifier.value();
			auto node_term = m_allocator.allocate<NodeTerm>();
			node_term->var = node_term_identifier;
			return node_term;
		} else {
			return {};
		}
	}

	inline std::optional<NodeExpression*> parse_expression() {
		if (auto term = parse_term()) {
			if (try_consume(TokenType::t_plus).has_value()) {
				auto binary_expression = m_allocator.allocate<NodeBinaryExpression>();
				auto binary_expression_addition = m_allocator.allocate<NodeBinaryExpressionAddition>();
				auto lhs_expression = m_allocator.allocate<NodeExpression>();
				lhs_expression->var = term.value();
				binary_expression_addition->lhs = lhs_expression;
				if (auto rhs = parse_expression()) {
					binary_expression_addition->rhs = rhs.value();
					binary_expression->add = binary_expression_addition;
					auto expression = m_allocator.allocate<NodeExpression>();
					expression->var = binary_expression;
					return expression;
				} else {
					std::cerr << "[PARSER] Invalid operator" << std::endl;
					exit(EXIT_FAILURE);
				}
			} else {
				auto expression = m_allocator.allocate<NodeExpression>();
				expression->var = term.value();
				return expression;
			}
		} else {
			return {};
		}
	}

	inline std::optional<NodeStatement *> parse_statement() {
		if (peek().value().type == TokenType::t_exit && peek(1).has_value() && peek(1).value().type == TokenType::t_open_parenthesis) {
			consume();
			consume();
			auto node_statement_exit = m_allocator.allocate<NodeStatementExit>();
			if (auto node_expression = parse_expression()) {
				node_statement_exit->expression = node_expression.value();
			} else {
				std::cerr << "[PARSER] Invalid expression" << std::endl;
				exit(EXIT_FAILURE);
			}
			try_consume(TokenType::t_close_parenthesis, "[PARSER] Expected `)`");
			try_consume(TokenType::t_semi_colon, "[PARSER] Expected `;`");
			
			auto node_statement = m_allocator.allocate<NodeStatement>();
			node_statement->var = node_statement_exit;
			return node_statement;
		} else if (peek().has_value() && peek().value().type == TokenType::t_variable && peek(1).has_value() && peek(1).value().type == TokenType::t_identifier && peek(2).has_value() && peek(2).value().type == TokenType::t_equal) {
			consume();
			auto node_statement_variable = m_allocator.allocate<NodeStatementVariable>();
			node_statement_variable->identifier = consume();
			consume();
			if (auto expression = parse_expression()) {
				node_statement_variable->expression = expression.value();
			} else {
				std::cerr << "[PARSER] Invalid expression" << std::endl;
				exit(EXIT_FAILURE);
			}
			try_consume(TokenType::t_semi_colon, "[PARSER] Expected `;`");
			auto node_statement = m_allocator.allocate<NodeStatement>();
			node_statement->var = node_statement_variable;
			return node_statement;
		} else {
			return {};
		}
	}

	inline std::optional<NodeProgram> parse_program() {
		NodeProgram program;
		while (peek().has_value()) {
			if (auto statement = parse_statement()) {
				program.statements.push_back(statement.value());
			} else {
				std::cerr << "[PARSER] Invalid statement" << std::endl;
				exit(EXIT_FAILURE);
			}
		}
		return program;
	}

private:
	[[nodiscard]] inline std::optional<Token> peek(int offset = 0) const {
		if (m_current_index + offset >= m_tokens.size()) {
			return {};
		} else {
			return m_tokens.at(m_current_index + offset);
		}
	}

	inline Token consume() {
		return m_tokens.at(m_current_index++);
	}

	inline Token try_consume(TokenType type, std::string error_message) {
		if (peek().has_value() && peek().value().type == type) {
			return consume();
		} else {
			std::cerr << error_message << std::endl;
			exit(EXIT_FAILURE);
		}
	}

	inline std::optional<Token> try_consume(TokenType type) {
		if (peek().has_value() && peek().value().type == type) {
			return consume();
		} else {
			return {};
		}
	}

	const std::vector<Token> m_tokens;
	size_t m_current_index = 0;
	ArenaAllocator m_allocator;
};