module sample

function radical_reverse2(x:Int)
    """
    This is the radical reverse with base of 2, so that bit operation is enabled
    Phi(2) = Sum(a_j(i)2^(-j-1))
    """
    phi = 0.0
    base = 1.0
    while x>0
        base = base/2
        phi = phi + (x & 1)*base
        x = x>>1
    end
end

function jitter ()
end

end
