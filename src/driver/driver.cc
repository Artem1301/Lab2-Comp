#include <boost/program_options.hpp>
#include <iostream>

#include "../ast/ast_dumper.hh"
#include "../parser/parser_driver.hh"
#include "../utils/errors.hh"
#include "../ast/int_evaluator.hh"

int main(int argc, char **argv) {
  std::vector<std::string> input_files;
  namespace po = boost::program_options;
  po::options_description options("Options");
  options.add_options()
  ("help,h", "describe arguments")
  ("dump-ast", "dump the parsed AST")
  ("trace-parser", "enable parser traces")
  ("trace-lexer", "enable lexer traces")
  ("verbose,v", "be verbose")
  ("eval,e", "evaluate the parsed expression")
  ("input-file", po::value(&input_files), "input Tiger file");

  po::positional_options_description positional;
  positional.add("input-file", 1);

  po::variables_map vm;
  po::store(po::command_line_parser(argc, argv)
                .options(options)
                .positional(positional)
                .run(),
            vm);
  po::notify(vm);

  if (vm.count("help")) {
    std::cout << options << "\n";
    return 1;
  }

  if (input_files.size() != 1) {
    utils::error("usage: dtiger [options] input-file");
  }

  ParserDriver parser_driver = ParserDriver(vm.count("trace-lexer"), vm.count("trace-parser"));

  if (!parser_driver.parse(input_files[0])) {
    utils::error("parser failed");
  }

// test edition
  if (vm.count("dump-ast") && vm.count("eval")) {
    utils::error("cannot use --dump-ast and --eval at the same time");
  }


  if (vm.count("dump-ast")) {
    ast::ASTDumper dumper(&std::cout, vm.count("verbose") > 0);
    parser_driver.result_ast->accept(dumper);
    dumper.nl();
  } else if (vm.count("eval")) {
    ast::types::IntEvaluator evaluator;
    int32_t result = parser_driver.result_ast->accept(evaluator);
    std::cout << "Result: " << result << std::endl;
  } 



  delete parser_driver.result_ast;
  return 0;
}
