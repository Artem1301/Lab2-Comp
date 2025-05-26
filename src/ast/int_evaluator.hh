#ifndef AST_INT_EVALUATOR_HH
#define AST_INT_EVALUATOR_HH

#include "nodes.hh" 
        #include "../utils/errors.hh" 
        #include "../utils/nolocation.hh" 

namespace ast {
inline namespace types {

class IntEvaluator : public ConstASTIntVisitor {
    public:

    virtual int32_t visit(const class IntegerLiteral &node) override;
    virtual int32_t visit(const class BinaryOperator &node) override;
    virtual int32_t visit(const class Sequence &node) override;
    virtual int32_t visit(const class IfThenElse &node) override;
    virtual int32_t visit(const class StringLiteral &node) override;
    virtual int32_t visit(const class Let &node) override;
    virtual int32_t visit(const class Identifier &node) override;
    virtual int32_t visit(const class VarDecl &node) override;
    virtual int32_t visit(const class FunDecl &node) override;
    virtual int32_t visit(const class FunCall &node) override;
    virtual int32_t visit(const class WhileLoop &node) override;
    virtual int32_t visit(const class ForLoop &node) override;
    virtual int32_t visit(const class Break &node) override;
    virtual int32_t visit(const class Assign &node) override;

    virtual ~IntEvaluator() {}
private:
    int32_t error_unimplemented(const location &loc, const std::string &node_type) const; 

};

}
        } 

        #endif 
