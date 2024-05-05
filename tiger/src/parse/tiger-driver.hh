/**
 ** \file parse/tiger-driver.hh
 ** \brief Declaration of parse::TigerDriver.
 */

#pragma once

#include <map>
#include <memory>
#include <stack>

#include <ast/fwd.hh>
#include <common.hh>
#include <misc/error.hh>
#include <misc/file-library.hh>
#include <parse/parsetiger.hh>
#include <parse/tweast.hh>

namespace parse
{
  /// Conduct the scanner and the parser.
  class TigerDriver
  {
  public:
    /// The parsed object is either a file, represented by the filename
    /// or a Tweast.
    using input_type = misc::variant<std::string, Tweast*>;

    TigerDriver(const misc::file_library& lib = misc::file_library());
    ~TigerDriver();

    friend class parser;
    /// Parse the Tiger file \a name.
    ast_type parse_file(const misc::path& name);
    /// Parse the Tweast \a s.  Extensions are enabled.
    ast_type parse(Tweast& s);
    /// Parse the string \a s.  Extensions are automatically disabled.
    ast_type parse(const std::string& s);

    /// Parse a Tiger prelude, return the list of chunk.
    ast::ChunkList* parse_import(const std::string& name, const location& loc);

    /// Return the error status of the parsing.
    const misc::error& error_get() const;

    /// The default prelude.
    const char* prelude() const;

    /// Set the scanner traces.
    TigerDriver& scan_trace(bool b = true);

    /// Set the parser traces.
    TigerDriver& parse_trace(bool b = true);

    /// Enable object extensions.
    TigerDriver& enable_object_extensions(bool b = true);

    /// Enable syntax extensions.
    TigerDriver& enable_extensions(bool b = true);

  private:
    /// \name Handling the scanner.
    /// \{
    /// Verbose scanning?
    bool scan_trace_p_ = getenv("SCAN");

    /// The list of open files, and the location of their request.
    std::map<misc::path, location> open_files_;
    /// \}

    /// \name Running the parse.
    /// \{
    /// Parse a Tiger program, return the AST.
    ast_type parse_();

    /// Parse a Tweast. \a extensions temporarily enable or disable
    /// extensions for the string parsing. This method is used to factor
    /// code between parse(Tweast) and parse(const std::string))
    ast_type parse_input(Tweast& input, bool extensions);

    /// Parse a Tiger prelude \a f, return the list of chunk.
    ast::ChunkList* parse_prelude(const std::string& f);

  public:
    /// The result of the parse.
    ast_type ast_;
    /// Parsing errors handler.
    misc::error error_;
    /// Verbose parsing?
    bool parse_trace_p_ = getenv("PARSE");
    /// \}

    /// The location requesting the import.
    location location_;
    /// The source to parse.
    input_type input_;
    /// The file library for imports.
    misc::file_library library_;
    /// Allow object extensions?
    bool enable_object_extensions_p_ = false;
    /// Allow language extensions (reserved identifiers, new keywords)?
    bool enable_extensions_p_ = false;
  };

} // namespace parse
