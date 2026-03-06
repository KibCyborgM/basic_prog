#include "long_number.hpp"

using tar::LongNumber;



void LongNumber::remove_leading_zeros() {
    if (this->length <= 1) return;
    
    int i = 0;
    while (i < this->length - 1 && this->numbers[i] == 0) {
        i++;
    }
    
    if (i > 0) {
        int new_len = this->length - i;
        int* new_numbers = new int[new_len];
        for (int j = 0; j < new_len; j++) {
            new_numbers[j] = this->numbers[i + j];
        }
        delete[] this->numbers;
        this->numbers = new_numbers;
        this->length = new_len;
    }
}


LongNumber::LongNumber() {
    this->sign = 1;
    this->length = 1;
    this->numbers = new int[1];
    this->numbers[0] = 0;
}

LongNumber::LongNumber(const char* const str) {
    int len = get_length(str);
    int start_index = 0;
    
    if (str[0] == '-') {
        this->length = len - 1;
        this->sign = 0;
        start_index = 1;
    } else {
        this->length = len;
        this->sign = 1;
    }
    
    this->numbers = new int[this->length];
    for (int i = 0; i < this->length; i++) {
        this->numbers[i] = str[start_index + i] - '0';
    }
}

LongNumber::LongNumber(const LongNumber& x) {
    this->length = x.length;
    this->sign = x.sign;
    this->numbers = new int[this->length];
    for (int i = 0; i < this->length; i++) {
        this->numbers[i] = x.numbers[i];
    }
}

LongNumber::LongNumber(LongNumber&& x) {
    this->length = x.length;
    this->sign = x.sign;
    this->numbers = x.numbers;
    
    x.length = 0;
    x.sign = 1;
    x.numbers = nullptr;
}

LongNumber::~LongNumber() {
    if (this->numbers != nullptr) {
        delete[] numbers;
        this->numbers = nullptr;
    }
}


LongNumber& LongNumber::operator=(const char* const str) {
    delete[] numbers;
    
    int len = get_length(str);
    int start_index = 0;
    
    if (str[0] == '-') {
        this->length = len - 1;
        this->sign = 0;
        start_index = 1;
    } else {
        this->length = len;
        this->sign = 1;
    }
    
    this->numbers = new int[this->length];
    for (int i = 0; i < this->length; i++) {
        this->numbers[i] = str[start_index + i] - '0';
    }
    return *this;
}

LongNumber& LongNumber::operator=(const LongNumber& x) {
    if (this == &x) return *this;
    
    delete[] this->numbers;
    this->length = x.length;
    this->sign = x.sign;
    this->numbers = new int[this->length];
    for (int i = 0; i < this->length; i++) {
        this->numbers[i] = x.numbers[i];
    }
    return *this;
}

LongNumber& LongNumber::operator=(LongNumber&& x) {
    if (this == &x) return *this;
    
    delete[] this->numbers;
    this->length = x.length;
    this->sign = x.sign;
    this->numbers = x.numbers;
    
    x.length = 0;
    x.sign = 1;
    x.numbers = nullptr;
    
    return *this;
}


bool LongNumber::operator==(const LongNumber& x) const {
    if (this->length != x.length || this->sign != x.sign)
        return false;
    for (int i = 0; i < this->length; i++) {
        if (this->numbers[i] != x.numbers[i])
            return false;
    }
    return true;
}

bool LongNumber::operator!=(const LongNumber& x) const {
    return !(*this == x);
}

bool LongNumber::operator>(const LongNumber& x) const {
    if (this->sign > x.sign) return true;
    if (this->sign < x.sign) return false;
    
    if (this->sign == 0) {
        if (this->length < x.length) return true;
        if (this->length > x.length) return false;
        for (int i = 0; i < this->length; i++) {
            if (this->numbers[i] < x.numbers[i]) return true;
            if (this->numbers[i] > x.numbers[i]) return false;
        }
        return false;
    }
    
    if (this->length > x.length) return true;
    if (this->length < x.length) return false;
    for (int i = 0; i < this->length; i++) {
        if (this->numbers[i] > x.numbers[i]) return true;
        if (this->numbers[i] < x.numbers[i]) return false;
    }
    return false;
}

bool LongNumber::operator<(const LongNumber& x) const {
    if (this->sign != x.sign) {
        return this->sign < x.sign;
    }
    
    if (this->length != x.length) {
        return (this->sign == 1) ? (this->length < x.length) : (this->length > x.length);
    }
    
    for (int i = 0; i < this->length; i++) {
        if (this->numbers[i] != x.numbers[i]) {
            return (this->sign == 1) ? (this->numbers[i] < x.numbers[i]) : (this->numbers[i] > x.numbers[i]);
        }
    }
    return false;
}


LongNumber LongNumber::operator+(const LongNumber& x) const {
    if (this->sign != x.sign) {
        LongNumber temp = x;
        temp.sign = 1 - temp.sign;
        return *this - temp;
    }
    
    int max_len = (this->length > x.length) ? this->length : x.length;
    
    LongNumber result;
    delete[] result.numbers;
    result.length = max_len + 1;
    result.sign = this->sign;
    result.numbers = new int[result.length]();
    
    int i = this->length - 1;
    int j = x.length - 1;
    int k = result.length - 1;
    int carry = 0;
    
    while (i >= 0 || j >= 0 || carry) {
        int sum = carry;
        if (i >= 0) sum += this->numbers[i--];
        if (j >= 0) sum += x.numbers[j--];
        result.numbers[k--] = sum % 10;
        carry = sum / 10;
    }
    
    result.remove_leading_zeros();
    return result;
}


LongNumber LongNumber::operator-(const LongNumber& x) const {
    if (this->sign != x.sign) {
        LongNumber temp = x;
        temp.sign = 1 - temp.sign;
        return *this + temp;
    }
    
    bool this_is_larger = true;
    if (this->length < x.length) {
        this_is_larger = false;
    } else if (this->length == x.length) {
        for (int i = 0; i < this->length; i++) {
            if (this->numbers[i] < x.numbers[i]) {
                this_is_larger = false;
                break;
            } else if (this->numbers[i] > x.numbers[i]) {
                break;
            }
        }
    }
    
    const LongNumber* larger = this_is_larger ? this : &x;
    const LongNumber* smaller = this_is_larger ? &x : this;
    
    LongNumber result;
    delete[] result.numbers;
    result.length = larger->length;
    result.sign = 1;
    result.numbers = new int[result.length]();
    
    int i = larger->length - 1;
    int j = smaller->length - 1;
    int k = result.length - 1;
    int borrow = 0;
    
    while (k >= 0) {
        int diff = larger->numbers[i--] - borrow;
        if (j >= 0) diff -= smaller->numbers[j--];
        
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result.numbers[k--] = diff;
    }
    
    if (this->sign == 0) {
        result.sign = this_is_larger ? 0 : 1;
    } else {
        result.sign = this_is_larger ? 1 : 0;
    }
    
    result.remove_leading_zeros();
    return result;
}


LongNumber LongNumber::operator*(const LongNumber& x) const {
    if (this->length == 1 && this->numbers[0] == 0) return LongNumber("0");
    if (x.length == 1 && x.numbers[0] == 0) return LongNumber("0");
    
    int result_len = this->length + x.length;
    int* result_arr = new int[result_len]();
    
    for (int i = this->length - 1; i >= 0; i--) {
        for (int j = x.length - 1; j >= 0; j--) {
            int product = this->numbers[i] * x.numbers[j];
            int pos1 = i + j;
            int pos2 = i + j + 1;
            
            int sum = product + result_arr[pos2];
            result_arr[pos2] = sum % 10;
            result_arr[pos1] += sum / 10;
        }
    }
    
    int start = 0;
    while (start < result_len - 1 && result_arr[start] == 0) {
        start++;
    }
    
    int actual_len = result_len - start;
    
    LongNumber result;
    delete[] result.numbers;
    result.length = actual_len;
    result.sign = (this->sign == x.sign) ? 1 : 0;
    result.numbers = new int[actual_len];
    
    for (int i = 0; i < actual_len; i++) {
        result.numbers[i] = result_arr[start + i];
    }
    
    delete[] result_arr;
    return result;
}


LongNumber LongNumber::operator/(const LongNumber& x) const {
    if (x.length == 1 && x.numbers[0] == 0) {
        return LongNumber("0");
    }
    
    bool result_negative = (this->sign != x.sign);
    
    LongNumber dividend = *this;
    LongNumber divisor = x;
    dividend.sign = 1;  
    divisor.sign = 1;
    
    if (dividend < divisor) {
        return LongNumber("0");
    }
    
    if (dividend == divisor) {
        LongNumber result("1");
        result.sign = result_negative ? 0 : 1;  
        return result;
    }
    
    LongNumber quotient("0");
    LongNumber remainder("0");
    
    for (int i = 0; i < dividend.length; i++) {  
		LongNumber temp;
        delete[] temp.numbers;
        temp.length = remainder.length + 1;
        temp.sign = 1;
        temp.numbers = new int[temp.length]();
        
        for (int j = 0; j < remainder.length; j++) {
            temp.numbers[j] = remainder.numbers[j];
        }
        temp.numbers[remainder.length] = dividend.numbers[i];
        temp.remove_leading_zeros();
        
        LongNumber digit("0");
        while (true) {
            LongNumber test = divisor * (digit + LongNumber("1"));
            if (test > temp) break;
            digit = digit + LongNumber("1");
        }
        
        remainder = temp - divisor * digit;
        
        if (!(quotient.length == 1 && quotient.numbers[0] == 0)) {
            LongNumber new_quotient;
            delete[] new_quotient.numbers;
            new_quotient.length = quotient.length + 1;
            new_quotient.sign = 1;
            new_quotient.numbers = new int[new_quotient.length]();
            
            for (int j = 0; j < quotient.length; j++) {
                new_quotient.numbers[j] = quotient.numbers[j];
            }
            new_quotient.numbers[quotient.length] = digit.numbers[0];
            quotient = new_quotient;
        } else {
            quotient = digit;
        }
    }
    
    quotient.remove_leading_zeros();
    
    quotient.sign = result_negative ? 0 : 1;
    
    return quotient;
}


LongNumber LongNumber::operator%(const LongNumber& x) const {
    if (x.length == 1 && x.numbers[0] == 0) {
        return LongNumber("0");
    }
    
    LongNumber quotient = *this / x;
    LongNumber remainder = *this - (x * quotient);
    
    return remainder;
}

bool LongNumber::is_negative() const noexcept {
    return this->sign == 0;
}

int LongNumber::get_length() const noexcept{
	return this->length;
}

int LongNumber::get_length(const char* const str) const noexcept {
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}


namespace tar {
	std::ostream& operator << (std::ostream& os, const LongNumber& x) {
		if (x.sign == 0) {
			os << '-';
		}
		for (int i = 0; i < x.length; i++) {
			os << x.numbers[i];
		}
		return os;
	}
}