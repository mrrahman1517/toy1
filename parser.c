#include "parser.h"

T_token lookahead_token;

T_token get_lookahead() {
    return lookahead_token;
}

void next_token() {
    lookahead_token = lex();
}

void parser_error() {
    fprintf(stderr, "parser error\n");
    exit(1);
}

T_statement_list parse_statement_list() {
    T_statement statement = parse_statement();
    if (get_lookahead()->kind == END) {
        return create_statement_list(statement, NULL);
    } else {
        return create_statement_list(statement, parse_statement_list());
    }
}

T_statement parse_statement() {
    T_expression expression = parse_expression();

    T_token semicolon = get_lookahead();
    if (semicolon->kind != SEMICOLON) {
        parser_error();
    }

    next_token();

    return create_statement(expression);
}

T_expression parse_expression() {
    T_token operand1 = get_lookahead();
    if (operand1->kind != NUMBER) {
        parser_error();
    }
    next_token();

    T_token op = get_lookahead();
    if (op->kind != OPERATOR) {
        parser_error();
    }
    next_token();

    T_token operand2 = get_lookahead();
    if (operand2->kind != NUMBER) {
        parser_error();
    }
    next_token();

    return create_expression(operand1, op, operand2);
}

T_expression create_expression(T_token operand1, T_token op, T_token operand2) {
    T_expression new_expression = (T_expression)malloc(sizeof(*new_expression));
    new_expression->operand1 = operand1;
    new_expression->op = op;
    new_expression->operand2 = operand2;
    return new_expression;
}