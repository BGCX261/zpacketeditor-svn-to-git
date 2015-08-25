#ifndef __ZParser_h__
#define __ZParser_h__

#pragma once

#include "Windows.h"

using namespace System;
using namespace System::Text::RegularExpressions;

/* Input literals */
enum Z_LITERAL_TYPE
{
	Z_LITERAL_TYPE_CHAR,   /* ASCII character */
	Z_LITERAL_TYPE_STRING, /* String */
	Z_LITERAL_TYPE_INT16,  /* 16-bit Integer */
	Z_LITERAL_TYPE_INT32,  /* 32-bit Integer */
};

namespace Z
{
	ref class ZParser
	{
		/* 1-byte literal */
		static Regex^ Byte1Expr = gcnew Regex(L"((?: *[0-9a-fA-F]{2} *){1})",
			RegexOptions::Compiled | RegexOptions::CultureInvariant);
		/* 2-byte literal: ((?: *[0-9a-fA-F]{2} *){2}) */
		static Regex^ Byte2Expr = gcnew Regex(L"((?: *[0-9a-fA-F]{2} *){2})",
			RegexOptions::Compiled | RegexOptions::CultureInvariant);
		/* 4-byte literal: ((?: *[0-9a-fA-F]{2} *){4}) */
		static Regex^ Byte4Expr = gcnew Regex(L"((?: *[0-9a-fA-F]{2} *){4})",
			RegexOptions::Compiled | RegexOptions::CultureInvariant);
		/* Multi-byte literal: ((?: *[0-9a-fA-F]{2} *){3,}) */
		static Regex^ ByteXExpr = gcnew Regex(L"((?: *[0-9a-fA-F]{2} *){3,})",
			RegexOptions::Compiled | RegexOptions::CultureInvariant);

		/* Strings: "(?<str>[\x20-\x21\x23-\x7F]*)" */
		static Regex^ StringsExpr = gcnew Regex(L"(?<str>\"[\\x20-\\x21\\x23-\\x7F]*\")",
			RegexOptions::Compiled | RegexOptions::CultureInvariant);

		/* Literal elements: (?:(?:^@(?<cmd>[0-9a-fA-F]{4}))|(?<hex>[0-9a-fA-F]{2})|\#(?<int>[\-\+]?\d+)(?:(?:\:(?<bit>1|2|4))?)|'(?<chr>[\x20-\x7F])'|"(?<str>[\x01\x21\x23-\x7F]*)") */
		static Regex^ LiteralExpr = gcnew Regex(L"(?:(?:^ *@(?<cmd>[0-9a-fA-F]{4}))|(?<hex>[0-9a-fA-F]{2})|\\#(?<int>[\\-\\+]?\\d+)(?:(?:\\:(?<bit>1|2|4))?)|'(?<chr>[\\x20-\\x7F])'|\"(?<str>[\\x01\\x21\\x23-\\x7F]*)\")",
			RegexOptions::Compiled | RegexOptions::CultureInvariant);
		/* Invalid elements: ( :?(?:[^ ]{1}) ) */
		static Regex^ InvalidExpr = gcnew Regex(L"( :?(?:[^ ]{1}) )",
			RegexOptions::Compiled | RegexOptions::CultureInvariant);
		/* Illegal characters: [^ 0-9a-fA-F] */
		static Regex^ IllegalExpr = gcnew Regex(L"[^ 0-9a-fA-F]",
			RegexOptions::Compiled | RegexOptions::CultureInvariant);

		/* Pattern matching */
		/* Literal elements: (?:(?:^@(?<cmd>[0-9a-fA-F]{4}))|(?<hex>[0-9a-fA-F]{2})|\#(?<int>[\-\+]?\d+)(?:(?:\:(?<bit>1|2|4))?)|'(?<chr>[\x20-\x7F])'|"(?<str>[\x01\x21\x23-\x7F]*)"|(?<wild>\*)|(?<mark>\?)) */
		static Regex^ LiteralPatternExpr = gcnew Regex(L"(?:(?:^ *@(?<cmd>[0-9a-fA-F]{4}))|(?<hex>[0-9a-fA-F]{2})|\\#(?<int>[\\-\\+]?\\d+)(?:(?:\\:(?<bit>1|2|4))?)|'(?<chr>[\\x20-\\x7F])'|\"(?<str>[\\x01\\x21\\x23-\\x7F]*)\"|(?<wild>\\*)|(?<mark>\\?))",
			RegexOptions::Compiled | RegexOptions::CultureInvariant);
		/* Invalid elements: ( :?(?:[^ \*\?]{1}) ) */
		static Regex^ InvalidPatternExpr = gcnew Regex(L"( :?(?:[^ \\*\\?]{1}) )",
			RegexOptions::Compiled | RegexOptions::CultureInvariant);

	private:
		/* Match evaluator for literals */
		static String^ GetByteCodeForLiteral ( Match^ match );
		/* Match evaluator for literals (patterns) */
		static String^ GetByteCodeForLiteralPattern ( Match^ match );

	public:
		/* Get a string literal for a series of bytes */
		static String^ GetLiteral ( String^ bytes, ::DWORD ltype );

		/* Get the byte code for a packet containing literals */
		static String^ GetByteCode ( String^ input );

		/* Get the byte code for a packet pattern */
		static String^ GetByteCodeForPattern ( String^ input );
	};
}

#endif /* __ZParser_h__ */
