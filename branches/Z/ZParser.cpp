#include "Z.h"
#include "Z_CLI.h"

using namespace Z;
using namespace System::Globalization;
using namespace System::Text;

/* Match evaluator for literals */
String^ ZParser::GetByteCodeForLiteral ( Match ^match )
{
	if ( match->Success ) {
		if ( match->Groups[L"cmd"]->Success )
			return String::Format(L"{0} {1}", match->Groups[L"cmd"]->Value->Substring(2,2), match->Groups[L"cmd"]->Value->Substring(0, 2));

		if ( match->Groups[L"hex"]->Success )
			return match->Groups[L"hex"]->Value->ToUpperInvariant();

		if ( match->Groups[L"int"]->Success ) {
			::INT64 i64;

			if ( Int64::TryParse(match->Groups[L"int"]->Value, NumberStyles::Integer, CultureInfo::InvariantCulture, i64) != true )
				return L"!";

			int width;

			/* Determine the minimum number of bytes needed to store this value */
			if ( ( ( i64 >= Byte::MinValue ) && ( i64 <= Byte::MaxValue ) ) || ( ( i64 >= SByte::MinValue ) && ( i64 <= SByte::MaxValue ) ) ) {
				width = 1;
			} else if ( ( ( i64 >= Int16::MinValue ) && ( i64 <= Int16::MaxValue ) ) || ( ( i64 >= UInt16::MinValue ) && ( i64 <= UInt16::MaxValue ) ) ) {
				width = 2;
			} else if ( ( ( i64 >= Int32::MinValue ) && ( i64 <= Int32::MaxValue ) ) || ( ( i64 >= UInt32::MinValue ) && ( i64 <= UInt32::MaxValue ) ) ) {
				width = 4;
			} else return L"!";

			/* If the user has requested that this value be stored at a higher width use it */
			if ( match->Groups[L"bit"]->Success ) {
				int i32 = width;

				if ( Int32::TryParse(match->Groups[L"bit"]->Value, NumberStyles::Integer, CultureInfo::InvariantCulture, i32) != true )
					return L"!";

				width = Math::Max(width, i32);
			}

			array<::BYTE>^ bytes;

			switch ( width ) {
				case 1:
					bytes = BitConverter::GetBytes(( i64 < 0 ) ? ((::INT8)i64) : ((::UINT8)i64));
					return String::Format(L"{0:X2}", bytes[0]);
				case 2:
					bytes = BitConverter::GetBytes(( i64 < 0 ) ? ((::INT16)i64) : ((::UINT16)i64));
					return String::Format(L"{0:X2} {1:X2}", bytes[0], bytes[1]);
				case 4:
					bytes = BitConverter::GetBytes(( i64 < 0 ) ? ((::INT32)i64) : ((::UINT32)i64));
					return String::Format(L"{0:X2} {1:X2} {2:X2} {3:X2}", bytes[0], bytes[1], bytes[2], bytes[3]);
				default:
					return L"!";
			}			
		}

		if ( match->Groups[L"chr"]->Success )
			return ((::BYTE)__toascii(match->Groups[L"chr"]->Value[0])).ToString(L"X2");

		if ( match->Groups[L"str"]->Success ) {
			if ( match->Groups[L"str"]->Value->Length < 1 )
				return String::Empty;

			if ( match->Groups[L"str"]->Value->Length > 0xFFFF )
				return L"!";

			StringBuilder^ sb = gcnew StringBuilder(match->Groups[L"str"]->Value->Length + 4);
			array<::BYTE>^ prefix = BitConverter::GetBytes((::USHORT)match->Groups[L"str"]->Value->Length);

			sb->Append(prefix[0].ToString(L"X2"));
			sb->Append(L" ");
			sb->Append(prefix[1].ToString(L"X2"));

			if ( match->Groups[L"str"]->Value->Length > 0 ) {
				for (  int n = 0, c; n < match->Groups[L"str"]->Value->Length; n++ ) {
					c = __toascii(match->Groups[L"str"]->Value[n]);

					sb->Append(L" ");
					sb->Append( ( ( c & 0xFF ) == 0x01 ) ? L"20" : ((::BYTE)c).ToString(L"X2") );
				}
			}

			return sb->ToString();
		}	
	}

	return L"!";
}

/* Match evaluator for literals */
String^ ZParser::GetByteCodeForLiteralPattern ( Match ^match )
{
	if ( match->Success ) {
		if ( match->Groups[L"cmd"]->Success )
			return String::Format(L"{0} {1}", match->Groups[L"cmd"]->Value->Substring(2,2), match->Groups[L"cmd"]->Value->Substring(0, 2));

		if ( match->Groups[L"hex"]->Success )
			return match->Groups[L"hex"]->Value->ToUpperInvariant();

		if ( match->Groups[L"int"]->Success ) {
			::INT64 i64;

			if ( Int64::TryParse(match->Groups[L"int"]->Value, NumberStyles::Integer, CultureInfo::InvariantCulture, i64) != true )
				return L"!";

			int width;

			/* Determine the minimum number of bytes needed to store this value */
			if ( ( ( i64 >= Byte::MinValue ) && ( i64 <= Byte::MaxValue ) ) || ( ( i64 >= SByte::MinValue ) && ( i64 <= SByte::MaxValue ) ) ) {
				width = 1;
			} else if ( ( ( i64 >= Int16::MinValue ) && ( i64 <= Int16::MaxValue ) ) || ( ( i64 >= UInt16::MinValue ) && ( i64 <= UInt16::MaxValue ) ) ) {
				width = 2;
			} else if ( ( ( i64 >= Int32::MinValue ) && ( i64 <= Int32::MaxValue ) ) || ( ( i64 >= UInt32::MinValue ) && ( i64 <= UInt32::MaxValue ) ) ) {
				width = 4;
			} else return L"!";

			/* If the user has requested that this value be stored at a higher width use it */
			if ( match->Groups[L"bit"]->Success ) {
				int i32 = width;

				if ( Int32::TryParse(match->Groups[L"bit"]->Value, NumberStyles::Integer, CultureInfo::InvariantCulture, i32) != true )
					return L"!";

				width = Math::Max(width, i32);
			}

			array<::BYTE>^ bytes;

			switch ( width ) {
				case 1:
					bytes = BitConverter::GetBytes(( i64 < 0 ) ? ((::INT8)i64) : ((::UINT8)i64));
					return String::Format(L"{0:X2}", bytes[0]);
				case 2:
					bytes = BitConverter::GetBytes(( i64 < 0 ) ? ((::INT16)i64) : ((::UINT16)i64));
					return String::Format(L"{0:X2} {1:X2}", bytes[0], bytes[1]);
				case 4:
					bytes = BitConverter::GetBytes(( i64 < 0 ) ? ((::INT32)i64) : ((::UINT32)i64));
					return String::Format(L"{0:X2} {1:X2} {2:X2} {3:X2}", bytes[0], bytes[1], bytes[2], bytes[3]);
				default:
					return L"!";
			}			
		}

		if ( match->Groups[L"chr"]->Success )
			return ((::BYTE)__toascii(match->Groups[L"chr"]->Value[0])).ToString(L"X2");

		if ( match->Groups[L"str"]->Success ) {
			if ( match->Groups[L"str"]->Value->Length < 1 )
				return String::Empty;

			if ( match->Groups[L"str"]->Value->Length > 0xFFFF )
				return L"!";

			StringBuilder^ sb = gcnew StringBuilder(match->Groups[L"str"]->Value->Length + 4);
			array<::BYTE>^ prefix = BitConverter::GetBytes((::USHORT)match->Groups[L"str"]->Value->Length);

			sb->Append(prefix[0].ToString(L"X2"));
			sb->Append(L" ");
			sb->Append(prefix[1].ToString(L"X2"));

			if ( match->Groups[L"str"]->Value->Length > 0 ) {
				for (  int n = 0, c; n < match->Groups[L"str"]->Value->Length; n++ ) {
					c = __toascii(match->Groups[L"str"]->Value[n]);

					sb->Append(L" ");
					sb->Append( ( ( c & 0xFF ) == 0x01 ) ? L"20" : ((::BYTE)c).ToString(L"X2") );
				}
			}

			return sb->ToString();
		}

		if ( match->Groups[L"wild"]->Success )
			return L"*";
		
		if ( match->Groups[L"mark"]->Success )
			return L"?";
	}

	return L"!";
}

String^ GetLiteralChar ( Match^ match )
{
	String^ buffer = match->Groups[1]->Value;
	String^ result = nullptr;
	array<::BYTE>^ bytes = gcnew array<::BYTE>(buffer->Length / 2);

	for ( int i = 0, j = 0; ( i < bytes->Length ) && ( ( j + 1 ) < buffer->Length ); i++, j+= 2 )
		bytes[i] = Byte::Parse(buffer->Substring(j, 2), NumberStyles::HexNumber, CultureInfo::InvariantCulture);

	if ( ( bytes[0] >= 0x20 ) && ( bytes[0] <= 0x7F ) )
		result = String::Format("'{0}'", (::WCHAR)bytes[0]);

	return ( result != nullptr ) ? result : buffer;
}

String^ GetLiteralString ( Match^ match )
{
	String^ buffer = match->Groups[1]->Value;
	String^ result = nullptr;
	::LONG32  nLength = buffer->Length / 2;
	::LPBYTE lpBytes = new ::BYTE [ nLength ];

	for ( int i = 0, j = 0; ( i < nLength ) && ( ( j + 1 ) < buffer->Length ); i++, j+= 2 )
		lpBytes[i] = Byte::Parse(buffer->Substring(j, 2), NumberStyles::HexNumber, CultureInfo::InvariantCulture);

	if ( *(::LPWORD)lpBytes == ( nLength - 2 ) ) {
		bool isstring = true;

		for ( int i = 2; i < nLength; i++ ) {
			if ( isprint(lpBytes[i]) == 0 ) {
				isstring = false;
				break;
			}
		}

		if ( isstring ) 
			result = String::Format("\"{0}\"", gcnew String((::LPSTR)( lpBytes + 2 ), 0, ( nLength - 2 )));
	}

	delete [] lpBytes;
	return ( result != nullptr ) ? result : buffer;
}

String^ GetLiteralInt16 ( Match^ match )
{
	String^ buffer = match->Groups[1]->Value;
	String^ result = nullptr;
	array<::BYTE>^ bytes = gcnew array<::BYTE>(buffer->Length / 2);

	for ( int i = 0, j = 0; ( i < bytes->Length ) && ( ( j + 1 ) < buffer->Length ); i++, j+= 2 )
		bytes[i] = Byte::Parse(buffer->Substring(j, 2), NumberStyles::HexNumber, CultureInfo::InvariantCulture);

	result = String::Format("#{0}:2", BitConverter::ToInt16(bytes, 0));
	return ( result != nullptr ) ? result : buffer;
}

String^ GetLiteralInt32 ( Match^ match )
{
	String^ buffer = match->Groups[1]->Value;
	String^ result = nullptr;
	array<::BYTE>^ bytes = gcnew array<::BYTE>(buffer->Length / 2);

	for ( int i = 0, j = 0; ( i < bytes->Length ) && ( ( j + 1 ) < buffer->Length ); i++, j+= 2 )
		bytes[i] = Byte::Parse(buffer->Substring(j, 2), NumberStyles::HexNumber, CultureInfo::InvariantCulture);

	result = String::Format("#{0}:4", BitConverter::ToInt32(bytes, 0));
	return ( result != nullptr ) ? result : buffer;
}

/* Get a string literal for a series of bytes */
String^ ZParser::GetLiteral ( String^ bytes, ::DWORD ltype )
{
	bytes = bytes->Replace(L" ", String::Empty);

	if ( String::IsNullOrEmpty(bytes) )
		return nullptr;

	switch ( ltype ) {
		case Z_LITERAL_TYPE_CHAR:
			return Byte1Expr->IsMatch(bytes) ? Byte1Expr->Replace(bytes, gcnew MatchEvaluator(&GetLiteralChar)) : nullptr;
		case Z_LITERAL_TYPE_STRING:
			return ByteXExpr->IsMatch(bytes) ? ByteXExpr->Replace(bytes, gcnew MatchEvaluator(&GetLiteralString)) : nullptr;
		case Z_LITERAL_TYPE_INT16:
			return Byte2Expr->IsMatch(bytes) ? Byte2Expr->Replace(bytes, gcnew MatchEvaluator(&GetLiteralInt16)) : nullptr;
		case Z_LITERAL_TYPE_INT32:
			return Byte4Expr->IsMatch(bytes) ? Byte4Expr->Replace(bytes, gcnew MatchEvaluator(&GetLiteralInt32)) : nullptr;
	}

	return nullptr;
}

String^ EscapeStrings ( Match^ match )
{
	if ( match->Success ) {
		if ( match->Groups[L"str"]->Success )
			return match->Groups[L"str"]->Value->Replace(L" ", L"\x01");
	}

	return String::Empty;
}

/* Get the byte code for a packet containing literals */
String^ ZParser::GetByteCode ( String^ input )
{
	if ( String::IsNullOrEmpty(input) )
		return nullptr;

	input = StringsExpr->Replace(input, gcnew MatchEvaluator(&EscapeStrings));
	input = LiteralExpr->Replace(input, L" $0 ");
	input = String::Concat(L" ", input, L" ");

	if ( InvalidExpr->IsMatch(input) )
		return nullptr;

	input = LiteralExpr->Replace(input, gcnew MatchEvaluator(&ZParser::GetByteCodeForLiteral));
	input = input->Replace(L" ", String::Empty);

	if ( IllegalExpr->IsMatch(input) )
		return nullptr;

	return input;
}

/* Get the byte code for a packet pattern */
String^ ZParser::GetByteCodeForPattern ( String^ input )
{	
	if ( String::IsNullOrEmpty(input) )
		return nullptr;

	input = StringsExpr->Replace(input, gcnew MatchEvaluator(&EscapeStrings));
	input = LiteralPatternExpr->Replace(input, L" $0 ");
	input = String::Concat(L" ", input, L" ");

	if ( InvalidPatternExpr->IsMatch(input) )
		return nullptr;

	input = LiteralPatternExpr->Replace(input, gcnew MatchEvaluator(&ZParser::GetByteCodeForLiteralPattern));
	input = input->Replace(L" ", String::Empty);
	return input;
}
