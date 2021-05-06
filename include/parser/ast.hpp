/*
 * This file is a part of the Kithare programming language source code.
 * The source code for Kithare programming language is distributed under the MIT license.
 * Copyright (C) 2021 Kithare Organization
 *
 * include/parser/ast.hpp
 * Declares AST node types.
 */

#pragma once

#include <complex>
#include <memory>
#include <vector>

#include "parser/token.hpp"
#include "utility/string.hpp"


namespace kh {
    class Ast;

    class AstImport;
    class AstClass;
    class AstStruct;
    class AstEnum;

    class AstBody;
    class AstIf;
    class AstWhile;
    class AstDoWhile;
    class AstFor;
    class AstStatement;

    class AstExpression;
    class AstIdentifierExpression;
    class AstUnaryExpression;
    class AstBinaryExpression;
    class AstTrinaryExpression;
    class AstSubscriptExpression;
    class AstCallExpression;
    class AstDeclarationExpression;
    class AstFunctionExpression;
    class AstScopeExpression;
    class AstConstValue;
    class AstTupleExpression;

    class Ast {
    public:
        std::vector<std::shared_ptr<kh::AstImport>> imports;
        std::vector<std::shared_ptr<kh::AstFunctionExpression>> functions;
        std::vector<std::shared_ptr<kh::AstClass>> classes;
        std::vector<std::shared_ptr<kh::AstStruct>> structs;
        std::vector<std::shared_ptr<kh::AstEnum>> enums;
        std::vector<std::shared_ptr<kh::AstDeclarationExpression>> variables;

        Ast(const std::vector<std::shared_ptr<kh::AstImport>>& _imports,
            const std::vector<std::shared_ptr<kh::AstFunctionExpression>>& _functions,
            const std::vector<std::shared_ptr<kh::AstClass>>& _classes,
            const std::vector<std::shared_ptr<kh::AstStruct>>& _structs,
            const std::vector<std::shared_ptr<kh::AstEnum>>& _enums,
            const std::vector<std::shared_ptr<kh::AstDeclarationExpression>>& _variables);
        virtual ~Ast() {}
    };

    class AstImport {
    public:
        size_t index;
        std::vector<std::u32string> path;
        bool is_include;
        std::u32string identifier;

        AstImport(const size_t _index, const std::vector<std::u32string>& _path, const bool _is_include,
                  const std::u32string& _identifier);
        virtual ~AstImport() {}
    };

    class AstClass {
    public:
        size_t index;
        std::u32string name;
        std::shared_ptr<kh::AstIdentifierExpression> base;
        std::vector<std::u32string> generic_args;
        std::vector<std::shared_ptr<kh::AstDeclarationExpression>> members;
        std::vector<std::shared_ptr<kh::AstFunctionExpression>> methods;

        AstClass(const size_t _index, const std::u32string& _name,
                 std::shared_ptr<kh::AstIdentifierExpression>& _base,
                 const std::vector<std::u32string>& _generic_args,
                 const std::vector<std::shared_ptr<kh::AstDeclarationExpression>>& _members,
                 const std::vector<std::shared_ptr<kh::AstFunctionExpression>>& _methods);
        virtual ~AstClass() {}
    };

    class AstStruct {
    public:
        size_t index;
        std::u32string name;
        std::shared_ptr<kh::AstIdentifierExpression> base;
        std::vector<std::shared_ptr<kh::AstDeclarationExpression>> members;

        AstStruct(const size_t _index, const std::u32string& _name,
                  std::shared_ptr<kh::AstIdentifierExpression>& _base,
                  const std::vector<std::shared_ptr<kh::AstDeclarationExpression>>& _members);
        virtual ~AstStruct() {}
    };

    class AstEnum {
    public:
        size_t index;
        std::u32string name;
        std::vector<std::u32string> members;
        std::vector<uint64_t> values;

        AstEnum(const size_t _index, const std::u32string& _name,
                const std::vector<std::u32string>& _members, const std::vector<uint64_t>& _values);
        virtual ~AstEnum() {}
    };

    class AstBody {
    public:
        size_t index;
        enum class Type { NONE, EXPRESSION, IF, WHILE, DO_WHILE, FOR, STATEMENT } type = Type::NONE;

        virtual ~AstBody() {}
    };

    class AstExpression : public kh::AstBody {
    public:
        enum class ExType {
            NONE,
            IDENTIFIER,
            UNARY,
            BINARY,
            TERNARY,
            SUBSCRIPT,
            CALL,
            DECLARE,
            FUNCTION,
            SCOPE,
            CONSTANT,
            TUPLE
        } expression_type = ExType::NONE;

        virtual ~AstExpression() {}
    };

    class AstIdentifierExpression : public kh::AstExpression {
    public:
        std::vector<std::u32string> identifiers;
        std::vector<std::shared_ptr<kh::AstIdentifierExpression>> generics;
        std::vector<std::vector<uint64_t>> generics_array;

        AstIdentifierExpression(
            const size_t _index, const std::vector<std::u32string>& _identifiers,
            const std::vector<std::shared_ptr<kh::AstIdentifierExpression>>& _generics,
            const std::vector<std::vector<uint64_t>>& _generics_array);
        virtual ~AstIdentifierExpression() {}
    };

    class AstUnaryExpression : public kh::AstExpression {
    public:
        kh::Operator operation;
        std::shared_ptr<kh::AstExpression> rvalue;

        AstUnaryExpression(const size_t _index, const kh::Operator _operation,
                           std::shared_ptr<kh::AstExpression>& _rvalue);
        virtual ~AstUnaryExpression() {}
    };

    class AstBinaryExpression : public kh::AstExpression {
    public:
        kh::Operator operation;
        std::shared_ptr<kh::AstExpression> lvalue;
        std::shared_ptr<kh::AstExpression> rvalue;

        AstBinaryExpression(const size_t _index, const kh::Operator _operation,
                            std::shared_ptr<kh::AstExpression>& _lvalue,
                            std::shared_ptr<kh::AstExpression>& _rvalue);
        virtual ~AstBinaryExpression() {}
    };

    class AstTernaryExpression : public kh::AstExpression {
    public:
        std::shared_ptr<kh::AstExpression> condition;
        std::shared_ptr<kh::AstExpression> value;
        std::shared_ptr<kh::AstExpression> otherwise;

        AstTernaryExpression(const size_t _index, std::shared_ptr<kh::AstExpression>& _condition,
                             std::shared_ptr<kh::AstExpression>& _value,
                             std::shared_ptr<kh::AstExpression>& _otherwise);
        virtual ~AstTernaryExpression() {}
    };

    class AstSubscriptExpression : public kh::AstExpression {
    public:
        std::shared_ptr<kh::AstExpression> expression;
        std::vector<std::shared_ptr<kh::AstExpression>> arguments;

        AstSubscriptExpression(const size_t _index, std::shared_ptr<kh::AstExpression>& _expression,
                               const std::vector<std::shared_ptr<kh::AstExpression>>& _arguments);
        virtual ~AstSubscriptExpression() {}
    };

    class AstCallExpression : public kh::AstExpression {
    public:
        std::shared_ptr<kh::AstExpression> expression;
        std::vector<std::shared_ptr<kh::AstExpression>> arguments;

        AstCallExpression(const size_t _index, std::shared_ptr<kh::AstExpression>& _expression,
                          const std::vector<std::shared_ptr<kh::AstExpression>>& _arguments);
        virtual ~AstCallExpression() {}
    };

    class AstDeclarationExpression : public kh::AstExpression {
    public:
        std::shared_ptr<kh::AstIdentifierExpression> var_type;
        std::vector<uint64_t> var_array;
        std::u32string var_name;
        std::shared_ptr<kh::AstExpression> expression;
        bool is_ref;
        bool is_static;
        bool is_public;

        AstDeclarationExpression(const size_t _index,
                                 std::shared_ptr<kh::AstIdentifierExpression>& _var_type,
                                 const std::vector<uint64_t>& _var_array,
                                 const std::u32string& _var_name,
                                 std::shared_ptr<kh::AstExpression>& _expression, const bool _is_ref,
                                 const bool _is_static, const bool _is_public);
        virtual ~AstDeclarationExpression() {}
    };

    class AstFunctionExpression : public kh::AstExpression {
    public:
        size_t index;
        std::vector<std::u32string> identifiers;
        std::vector<std::u32string> generic_args;

        std::shared_ptr<kh::AstIdentifierExpression> return_type;
        std::vector<uint64_t> return_array;
        bool is_return_ref;

        std::vector<std::shared_ptr<kh::AstDeclarationExpression>> arguments;
        std::vector<std::shared_ptr<kh::AstBody>> body;
        bool is_static;
        bool is_public;

        AstFunctionExpression(
            const size_t _index, const std::vector<std::u32string>& _identifiers,
            const std::vector<std::u32string>& _generic_args,
            const std::vector<uint64_t>& _return_array,
            std::shared_ptr<kh::AstIdentifierExpression>& _return_type, const bool _is_return_ref,
            const std::vector<std::shared_ptr<kh::AstDeclarationExpression>>& _arguments,
            const std::vector<std::shared_ptr<kh::AstBody>>& _body, const bool _is_static,
            const bool _is_public);
        virtual ~AstFunctionExpression() {}
    };

    class AstScopeExpression : public kh::AstExpression {
    public:
        std::shared_ptr<kh::AstExpression> expression;
        std::vector<std::u32string> identifiers;

        AstScopeExpression(const size_t _index, std::shared_ptr<kh::AstExpression>& _expression,
                           const std::vector<std::u32string>& _identifiers);
        virtual ~AstScopeExpression() {}
    };

    class AstConstValue : public kh::AstExpression {
    public:
        enum class ValueType {
            CHARACTER,
            UINTEGER,
            INTEGER,
            FLOATING,
            COMPLEX,
            BUFFER,
            STRING
        } value_type;

        union {
            char32_t character;
            uint64_t uinteger;
            int64_t integer;
            double floating;
        };

        std::complex<double> complex = 0;
        std::string buffer = "";
        std::u32string string = U"";

        AstConstValue(
            const size_t _index, const char32_t _character,
            const kh::AstConstValue::ValueType _value_type = kh::AstConstValue::ValueType::CHARACTER);
        AstConstValue(
            const size_t _index, const uint64_t _uinteger,
            const kh::AstConstValue::ValueType _value_type = kh::AstConstValue::ValueType::UINTEGER);
        AstConstValue(
            const size_t _index, const int64_t _integer,
            const kh::AstConstValue::ValueType _value_type = kh::AstConstValue::ValueType::INTEGER);
        AstConstValue(
            const size_t _index, const double _floating,
            const kh::AstConstValue::ValueType _value_type = kh::AstConstValue::ValueType::FLOATING);
        AstConstValue(
            const size_t _index, const std::complex<double> _complex,
            const kh::AstConstValue::ValueType _value_type = kh::AstConstValue::ValueType::COMPLEX);
        AstConstValue(
            const size_t _index, const std::string& _buffer,
            const kh::AstConstValue::ValueType _value_type = kh::AstConstValue::ValueType::BUFFER);
        AstConstValue(
            const size_t _index, const std::u32string& _string,
            const kh::AstConstValue::ValueType _value_type = kh::AstConstValue::ValueType::STRING);
        virtual ~AstConstValue() {}
    };

    class AstTupleExpression : public kh::AstExpression {
    public:
        std::vector<std::shared_ptr<kh::AstExpression>> elements;

        AstTupleExpression(const size_t _index,
                           const std::vector<std::shared_ptr<kh::AstExpression>>& _elements);
        virtual ~AstTupleExpression() {}
    };

    class AstIf : public kh::AstBody {
    public:
        std::vector<std::shared_ptr<kh::AstExpression>>
            conditions; /* Including the else if conditions */
        std::vector<std::vector<std::shared_ptr<kh::AstBody>>> bodies;
        std::vector<std::shared_ptr<kh::AstBody>> else_body;

        AstIf(const size_t _index, const std::vector<std::shared_ptr<kh::AstExpression>>& _conditions,
              const std::vector<std::vector<std::shared_ptr<kh::AstBody>>>& _bodies,
              const std::vector<std::shared_ptr<kh::AstBody>>& _else_body);
        virtual ~AstIf() {}
    };

    class AstWhile : public kh::AstBody {
    public:
        std::shared_ptr<kh::AstExpression> condition;
        std::vector<std::shared_ptr<kh::AstBody>> body;

        AstWhile(const size_t _index, std::shared_ptr<kh::AstExpression>& _condition,
                 const std::vector<std::shared_ptr<kh::AstBody>>& _body);
        virtual ~AstWhile() {}
    };

    class AstDoWhile : public kh::AstBody {
    public:
        std::shared_ptr<kh::AstExpression> condition;
        std::vector<std::shared_ptr<kh::AstBody>> body;

        AstDoWhile(const size_t _index, std::shared_ptr<kh::AstExpression>& _condition,
                   const std::vector<std::shared_ptr<kh::AstBody>>& _body);
        virtual ~AstDoWhile() {}
    };

    class AstFor : public kh::AstBody {
    public:
        std::shared_ptr<kh::AstExpression> target;
        std::shared_ptr<kh::AstExpression> iterator;
        std::vector<std::shared_ptr<kh::AstBody>> body;

        AstFor(const size_t _index, std::shared_ptr<kh::AstExpression>& _target,
               std::shared_ptr<kh::AstExpression>& _iterator,
               const std::vector<std::shared_ptr<kh::AstBody>>& _body);
        virtual ~AstFor() {}
    };

    class AstStatement : public kh::AstBody {
    public:
        enum class Type { CONTINUE, BREAK, RETURN } statement_type;
        std::shared_ptr<kh::AstExpression> expression;

        AstStatement(const size_t _index, const kh::AstStatement::Type _statement_type,
                     std::shared_ptr<kh::AstExpression>& _expression);
        virtual ~AstStatement() {}
    };
}
