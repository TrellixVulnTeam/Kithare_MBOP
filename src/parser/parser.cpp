/*
 * This file is a part of the Kithare programming language source code.
 * The source code for Kithare programming language is distributed under the MIT license.
 * Copyright (C) 2021 Kithare Organization
 */

#include <kithare/parser.hpp>
#include <kithare/string.hpp>


std::u32string kh::LexException::format() const {
    return this->what + U" at line " + kh::str((uint64_t)this->line) + U" column " +
           kh::str((uint64_t)this->column);
}

std::u32string kh::ParseException::format() const {
    return this->what + U" at line " + kh::str((uint64_t)this->token.line) + U" column " +
           kh::str((uint64_t)this->token.column);
}

kh::Parser::Parser() {}

kh::Parser::Parser(const std::u32string& _source) : source(_source) {}

kh::Parser::Parser(const std::vector<kh::Token>& _tokens) : tokens(_tokens) {}

kh::Parser::~Parser() {}
