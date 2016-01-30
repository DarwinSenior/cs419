module sample2d
import Gadfly: plot

export visualise, hammersley, uniform2d, multi_jittered

function visualise(xy::Array{Float64, 3})
    nx, ny = size(xy, 1, 2)
    X = reshape(xy[:,:,1], nx*ny)
    Y = reshape(xy[:,:,2], nx*ny)
    plot(x=X, y=Y)
end

"""
This is the radical reverse with base of 2, so that bit operation is enabled
Phi(2) = Sum(a_j(i)2^(-j-1))
"""
function radical_reverse2(x::Int)
    phi = 0.0
    base = 1.0
    while x>0
        base = base/2
        phi = phi + (x & 1)*base
        x = x>>1
    end
end

function hammersley(n::Int)
    samples = Array(Float64, (n, n, 2))
    for x in 1:n
        for y in 1:n
            index = ((x-1)*n+y)
            @inbounds samples[x,y,1] = index/n^2
            @inbounds samples[x,y,2] = radical_reverse2(index)
        end
    end
end

function uniform2d(n::Int)
    samples = Array(Float64, (n, n, 2))
    shift = 0.5/n
    for x in 1:n
        for y in 1:n
            @inbounds samples[x,y,1] = x/n-shift
            @inbounds samples[x,y,2] = y/n-shift
        end
    end
    return samples
end

function multi_jittered(n::Int)
    samples = Array(Float64, (n, n, 2))
    rand_order = collect(1:n)
    for x in 1:n
        shuffle!(rand_order)
        for y in 1:n
            @inbounds samples[x,y,1] = (rand_order[y]+x*n)/n^2
        end
    end
    for x in 1:n
        shuffle!(rand_order)
        for y in 1:n
            @inbounds samples[x,y,2] = (rand_order[x]+y*n)/n^2
        end
    end
    return samples
end

end
