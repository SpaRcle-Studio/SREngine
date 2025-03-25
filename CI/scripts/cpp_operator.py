import enum


class OperatorType(enum.Enum):
    NONE = 0
    ADDITION = 1 # operator+
    SUBTRACTION = 2 # operator-
    MULTIPLICATION = 3 # operator*
    DIVISION = 4 # operator/
    MODULUS = 5 # operator%
    INCREMENT = 6 # operator++
    DECREMENT = 7 # operator--
    BITWISE_AND = 8 # operator&
    BITWISE_OR = 9 # operator|
    BITWISE_XOR = 10 # operator^
    BITWISE_NOT = 11 # operator~
    LOGICAL_AND = 12 # operator&&
    LOGICAL_OR = 13 # operator||
    LOGICAL_NOT = 14 # operator!
    EQUALITY = 15 # operator==
    INEQUALITY = 16 # operator!=
    LESS_THAN = 17 # operator<
    GREATER_THAN = 18 # operator>
    LESS_THAN_OR_EQUAL = 19 # operator<=
    GREATER_THAN_OR_EQUAL = 20 # operator>=
    ASSIGNMENT = 21 # operator=
    ADDITION_ASSIGNMENT = 22 # operator+=
    SUBTRACTION_ASSIGNMENT = 23 # operator-=
    MULTIPLICATION_ASSIGNMENT = 24 # operator*=
    DIVISION_ASSIGNMENT = 25 # operator/=
    MODULUS_ASSIGNMENT = 26 # operator%=
    BITWISE_AND_ASSIGNMENT = 27 # operator&=
    BITWISE_OR_ASSIGNMENT = 28 # operator|=
    BITWISE_XOR_ASSIGNMENT = 29 # operator^=
    BITWISE_LEFT_SHIFT = 30 # operator<<
    BITWISE_RIGHT_SHIFT = 31 # operator>>
    BITWISE_LEFT_SHIFT_ASSIGNMENT = 32 # operator<<=
    BITWISE_RIGHT_SHIFT_ASSIGNMENT = 33 # operator>>=
    SUBSCRIPT = 34 # operator[]
    CALL = 35 # operator()

    @staticmethod
    def from_string(op_str: str):
        op_str = op_str.strip()
        if op_str == 'operator+':
            return OperatorType.ADDITION
        elif op_str == 'operator-':
            return OperatorType.SUBTRACTION
        elif op_str == 'operator*':
            return OperatorType.MULTIPLICATION
        elif op_str == 'operator/':
            return OperatorType.DIVISION
        elif op_str == 'operator%':
            return OperatorType.MODULUS
        elif op_str == 'operator++':
            return OperatorType.INCREMENT
        elif op_str == 'operator--':
            return OperatorType.DECREMENT
        elif op_str == 'operator&':
            return OperatorType.BITWISE_AND
        elif op_str == 'operator|':
            return OperatorType.BITWISE_OR
        elif op_str == 'operator^':
            return OperatorType.BITWISE_XOR
        elif op_str == 'operator~':
            return OperatorType.BITWISE_NOT
        elif op_str == 'operator&&':
            return OperatorType.LOGICAL_AND
        elif op_str == 'operator||':
            return OperatorType.LOGICAL_OR
        elif op_str == 'operator!':
            return OperatorType.LOGICAL_NOT
        elif op_str == 'operator==':
            return OperatorType.EQUALITY
        elif op_str == 'operator!=':
            return OperatorType.INEQUALITY
        elif op_str == 'operator<':
            return OperatorType.LESS_THAN
        elif op_str == 'operator>':
            return OperatorType.GREATER_THAN
        elif op_str == 'operator<=':
            return OperatorType.LESS_THAN_OR_EQUAL
        elif op_str == 'operator>=':
            return OperatorType.GREATER_THAN_OR_EQUAL
        elif op_str == 'operator=':
            return OperatorType.ASSIGNMENT
        elif op_str == 'operator+=':
            return OperatorType.ADDITION_ASSIGNMENT
        elif op_str == 'operator-=':
            return OperatorType.SUBTRACTION_ASSIGNMENT
        elif op_str == 'operator*=':
            return OperatorType.MULTIPLICATION_ASSIGNMENT
        elif op_str == 'operator/=':
            return OperatorType.DIVISION_ASSIGNMENT
        elif op_str == 'operator%=':
            return OperatorType.MODULUS_ASSIGNMENT
        elif op_str == 'operator&=':
            return OperatorType.BITWISE_AND_ASSIGNMENT
        elif op_str == 'operator|=':
            return OperatorType.BITWISE_OR_ASSIGNMENT
        elif op_str == 'operator^=':
            return OperatorType.BITWISE_XOR_ASSIGNMENT
        elif op_str == 'operator<<':
            return OperatorType.BITWISE_LEFT_SHIFT
        elif op_str == 'operator>>':
            return OperatorType.BITWISE_RIGHT_SHIFT
        elif op_str == 'operator<<=':
            return OperatorType.BITWISE_LEFT_SHIFT_ASSIGNMENT
        elif op_str == 'operator>>=':
            return OperatorType.BITWISE_RIGHT_SHIFT_ASSIGNMENT
        elif op_str == 'operator[]':
            return OperatorType.SUBSCRIPT
        elif op_str == 'operator()':
            return OperatorType.CALL
        else:
            raise ValueError(f'Unknown operator string: {op_str}')

    @staticmethod
    def to_string(op_enum):
        if op_enum == OperatorType.ADDITION:
            return 'operator+'
        elif op_enum == OperatorType.SUBTRACTION:
            return 'operator-'
        elif op_enum == OperatorType.MULTIPLICATION:
            return 'operator*'
        elif op_enum == OperatorType.DIVISION:
            return 'operator/'
        elif op_enum == OperatorType.MODULUS:
            return 'operator%'
        elif op_enum == OperatorType.INCREMENT:
            return 'operator++'
        elif op_enum == OperatorType.DECREMENT:
            return 'operator--'
        elif op_enum == OperatorType.BITWISE_AND:
            return 'operator&'
        elif op_enum == OperatorType.BITWISE_OR:
            return 'operator|'
        elif op_enum == OperatorType.BITWISE_XOR:
            return 'operator^'
        elif op_enum == OperatorType.BITWISE_NOT:
            return 'operator~'
        elif op_enum == OperatorType.LOGICAL_AND:
            return 'operator&&'
        elif op_enum == OperatorType.LOGICAL_OR:
            return 'operator||'
        elif op_enum == OperatorType.LOGICAL_NOT:
            return 'operator!'
        elif op_enum == OperatorType.EQUALITY:
            return 'operator=='
        elif op_enum == OperatorType.INEQUALITY:
            return 'operator!='
        elif op_enum == OperatorType.LESS_THAN:
            return 'operator<'
        elif op_enum == OperatorType.GREATER_THAN:
            return 'operator>'
        elif op_enum == OperatorType.LESS_THAN_OR_EQUAL:
            return 'operator<='
        elif op_enum == OperatorType.GREATER_THAN_OR_EQUAL:
            return 'operator>='
        elif op_enum == OperatorType.ASSIGNMENT:
            return 'operator='
        elif op_enum == OperatorType.ADDITION_ASSIGNMENT:
            return 'operator+='
        elif op_enum == OperatorType.SUBTRACTION_ASSIGNMENT:
            return 'operator-='
        elif op_enum == OperatorType.MULTIPLICATION_ASSIGNMENT:
            return 'operator*='
        elif op_enum == OperatorType.DIVISION_ASSIGNMENT:
            return 'operator/='
        elif op_enum == OperatorType.MODULUS_ASSIGNMENT:
            return 'operator%='
        elif op_enum == OperatorType.BITWISE_AND_ASSIGNMENT:
            return 'operator&='
        elif op_enum == OperatorType.BITWISE_OR_ASSIGNMENT:
            return 'operator|='
        elif op_enum == OperatorType.BITWISE_XOR_ASSIGNMENT:
            return 'operator^='
        elif op_enum == OperatorType.BITWISE_LEFT_SHIFT:
            return 'operator<<'
        elif op_enum == OperatorType.BITWISE_RIGHT_SHIFT:
            return 'operator>>'
        elif op_enum == OperatorType.BITWISE_LEFT_SHIFT_ASSIGNMENT:
            return 'operator<<='
        elif op_enum == OperatorType.BITWISE_RIGHT_SHIFT_ASSIGNMENT:
            return 'operator>>='
        elif op_enum == OperatorType.SUBSCRIPT:
            return 'operator[]'
        elif op_enum == OperatorType.CALL:
            return 'operator()'
        else:
            raise ValueError(f'Unknown operator enum: {op_enum}')


