#pragma once
#include <memory>
#include <string>
#include <vector>
#include <map>

// Nix AST for Nix Expressions
struct NixExpr {
  enum class Type { Literal, Ident, Apply, Lambda, AttrSet } type;

  // Literal
  std::string litValue;

  // Identifier
  std::string name;

  // Function application: func(args...)
  std::shared_ptr<NixExpr> func;
  std::vector<std::shared_ptr<NixExpr>> args;

  // Lambda: { params }: body
  std::vector<std::string> params;
  std::shared_ptr<NixExpr> body;

  // Attribute set: { key = expr; ... }
  std::map<std::string, std::shared_ptr<NixExpr>> attrs;

  // Format to Nix syntax
  std::string toNix(unsigned indent = 0) const;
};