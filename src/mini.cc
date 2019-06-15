#include <string>

#include "ModuleInstantiation.h"
#include "Tree.h"
#include "builtincontext.h"
#include "comment.h"
#include "handle_dep.h"
#include "node.h"
#include "openscad.h"
#include "parameter/parameterset.h"

std::string commandline_commands;

int main() {
  std::string new_output_file = "test.csg";
  std::string original_path = "test.scad";
  std::string filename = "test.scad";
  std::string commandline_commands = "";
  std::string parameterFile = "";
  std::string setName = "";

  Tree tree;
  boost::filesystem::path doc(filename);
  tree.setDocumentPath(doc.remove_filename().string());

  BuiltinContext top_ctx;
  const bool preview = false;
  top_ctx.set_variable("$preview", ValuePtr(preview));

  FileModule *root_module;
  ModuleInstantiation root_inst("group");
  AbstractNode *root_node;
  AbstractNode *absolute_root_node;
  shared_ptr<const Geometry> root_geom;

  handle_dep(filename);

  std::ifstream ifs(filename.c_str());
  if (!ifs.is_open()) {
    PRINTB("Can't open input file '%s'!\n", filename.c_str());
    return 1;
  }
  std::string text((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
  text += "\n\x03\n" + commandline_commands;
  if (!parse(root_module, text, filename, filename, false)) {
    delete root_module;  // parse failed
    root_module = nullptr;
  }
  if (!root_module) {
    PRINTB("Can't parse file '%s'!\n", filename.c_str());
    return 1;
  }

  // add parameter to AST
  CommentParser::collectParameters(text.c_str(), root_module);
  if (!parameterFile.empty() && !setName.empty()) {
    ParameterSet param;
    param.readParameterSet(parameterFile);
    param.applyParameterSet(root_module, setName);
  }
    
  root_module->handleDependencies();

  auto fpath = fs::absolute(fs::path(filename));
  auto fparent = fpath.parent_path();
  fs::current_path(fparent);
  top_ctx.setDocumentPath(fparent.string());

  AbstractNode::resetIndexCounter();
  absolute_root_node = root_module->instantiate(&top_ctx, &root_inst, nullptr);

  // Do we have an explicit root node (! modifier)?
  if (!(root_node = find_root_tag(absolute_root_node))) {
    root_node = absolute_root_node;
  }
  tree.setRoot(root_node);

  {
    fs::current_path(original_path);
    std::ofstream fstream(new_output_file);
    if (!fstream.is_open()) {
      PRINTB("Can't open file \"%s\" for export", new_output_file);
    }
    else {
      fs::current_path(fparent); // Force exported filenames to be relative to document path
      fstream << tree.getString(*root_node, "\t") << "\n";
      fstream.close();
    }
  }
  delete root_node;
  return 0;
}
