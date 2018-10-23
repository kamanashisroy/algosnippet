

def get_hash_by_string(string):
    result = 0;
    for x in string:
        result = (result*256 + ord(x))%101
    return result

def get_rolling_hash_multiplier(word_len):
    result = 1
    for i in xrange(word_len):
        result = (result*256)%101
    return result

def get_rolling_hash_by_char(rolling_hash, rem_ch, add_ch, mul):
    return (rolling_hash*256 - (rem_ch*mul)%101 + add_ch)
	%101 # Mod is done at the end to keep the size of the hash at bay

def count_substring(string, sub_string):
    count = 0
    our_hash = get_hash_by_string(sub_string)
    mul = get_rolling_hash_multiplier(len(sub_string))
    rolling_hash = get_hash_by_string(string[:len(sub_string)])
    if(rolling_hash == our_hash):
        count = count + 1
    #print mul
    for i in xrange(len(sub_string),len(string),1):
        #print string[i]
        start = i - len(sub_string)
        #print string[start]
        rolling_hash = get_rolling_hash_by_char(rolling_hash
                                                , ord(string[start])
                                                , ord(string[i]), mul);
        if(rolling_hash == our_hash):
            count = count + 1
    return count

if __name__ == '__main__':
    haystack = raw_input()
    niddle = raw_input()
    print count_substring(haystack, niddle)
