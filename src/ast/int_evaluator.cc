#include "int_evaluator.hh" 
#include "nodes.hh"
#include "../utils/errors.hh"
#include <string>     
#include <vector>
#include <cstdint>     

namespace ast {
   inline namespace types {

    using yy::location;

    int32_t IntEvaluator::error_unimplemented(const location &loc, const std::string &node_type) const {
        utils::error(loc, "evaluation of " + node_type + " nodes is not yet implemented");
        return 0;
    }

    int32_t IntEvaluator::visit(const class StringLiteral &node)  {
       return error_unimplemented(node.loc, "StringLiteral");
    }

    int32_t IntEvaluator::visit(const class Let &node)  {
         return error_unimplemented(node.loc, "Let");
    }

    int32_t IntEvaluator::visit(const class Identifier &node)  {
         return error_unimplemented(node.loc, "Identifier");
    }

    int32_t IntEvaluator::visit(const class VarDecl &node)  {
         return error_unimplemented(node.loc, "VarDecl");
    }

    int32_t IntEvaluator::visit(const class FunDecl &node)  {
         return error_unimplemented(node.loc, "FunDecl");
    }

    int32_t IntEvaluator::visit(const class FunCall &node)  {
         return error_unimplemented(node.loc, "FunCall");
    }

    int32_t IntEvaluator::visit(const class WhileLoop &node)  {
         return error_unimplemented(node.loc, "WhileLoop");
    }

    int32_t IntEvaluator::visit(const class ForLoop &node)  {
         return error_unimplemented(node.loc, "ForLoop");
    }

    int32_t IntEvaluator::visit(const class Break &node)  {
         return error_unimplemented(node.loc, "Break");
    }

    int32_t IntEvaluator::visit(const class Assign &node)  {
         return error_unimplemented(node.loc, "Assign");
    }


    int32_t IntEvaluator::visit(const class IntegerLiteral &node)  {
        return node.value;
    }

    int32_t IntEvaluator::visit(const class BinaryOperator &node)  {

        int32_t left_val = node.get_left().accept(*this);
        int32_t right_val = node.get_right().accept(*this);

        switch (node.op) {
            case o_plus: return left_val + right_val;
            case o_minus: return left_val - right_val;
            case o_times: return left_val * right_val;
            case o_divide:
               if (right_val == 0) {
                    utils::error(node.loc, "division by zero");
                    return 0;
               }
               return left_val / right_val;
            case o_eq: return left_val == right_val ? 1 : 0;
            case o_neq: return left_val != right_val ? 1 : 0;
            case o_lt: return left_val < right_val ? 1 : 0;
            case o_le: return left_val <= right_val ? 1 : 0;
            case o_gt: return left_val > right_val ? 1 : 0;
            case o_ge: return left_val >= right_val ? 1 : 0;
            default:
                 utils::error(node.loc, "unknown binary operator");
                 return 0;
        }
    }

    int32_t IntEvaluator::visit(const class Sequence &node)  {

         const auto &exprs = node.get_exprs();
         if (exprs.empty()) {
             utils::error(node.loc, "evaluation of empty sequence () is not allowed");
             return 0;
         }

         int32_t result = 0;
         for (const auto &expr : exprs) {
             result = expr->accept(*this);
         }
         return result;
    }

    int32_t IntEvaluator::visit(const class IfThenElse &node)  {
         int32_t condition_val = node.get_condition().accept(*this);

         if (condition_val != 0) {
             return node.get_then_part().accept(*this);
         } else {
             return node.get_else_part().accept(*this);
         }
    }


    }
    }
