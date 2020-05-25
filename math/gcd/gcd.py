#!python

class gcd:
    def calc_gcd_recursive(x,y):
        if x < y:
            if 0 == x:
                return y
            return gcd.calc_gcd_recursive(x, y-x)
        elif x == y:
            return x
        else:
            return gcd.calc_gcd_recursive(y,x)

    def calc_gcd(x,y):
        while True:
            if 0 == x:
                return y
            elif 0 == y:
                return x
            #elif 1 == x or 1 == y:
            #    return 1
            elif x < y:
                y -= x
            else:
                x -= y


if __name__ == "__main__":
    print("gcd(6,12)=%d" % gcd.calc_gcd(6,12))
    print("gcd(12,6)=%d" % gcd.calc_gcd(12,6))
    print("gcd(16,12)=%d" % gcd.calc_gcd(16,12))
    print("gcd(12,16)=%d" % gcd.calc_gcd(12,16))
    print("gcd(12,16)=%d" % gcd.calc_gcd(1,200))
    print("gcd(6,12)=%d" % gcd.calc_gcd_recursive(6,12))
    print("gcd(12,6)=%d" % gcd.calc_gcd_recursive(12,6))
    print("gcd(16,12)=%d" % gcd.calc_gcd_recursive(16,12))
    print("gcd(12,16)=%d" % gcd.calc_gcd_recursive(12,16))
    print("gcd(12,16)=%d" % gcd.calc_gcd_recursive(1,200))
