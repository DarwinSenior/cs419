"""
This test is for comparing the C-struct like vector vs tuple vs array
on the performance of basic operation of 3d-vector including dot product and cross product
"""
module comparison
    immutable Vec3s
        x::Float64
        y::Float64
        z::Float64
    end
    import Base.dot
    typealias Vec3t Tuple{Float64, Float64, Float64}

    typealias Vec3a Vector{Float64}

    dot(a::Vec3s, b::Vec3s)=a.x*b.x+a.y*b.y+a.z*b.z
    dot(a::Vec3t, b::Vec3t)=a[1]*b[1]+a[2]*b[2]+a[3]*b[3]

    function start_profile{T}(data::Vector{T})
        l = length(data)
        for i in 1:l
            dot(data[i], data[l-i+1])
        end
        nothing
    end
    generateS(x::Int64) = [Vec3s(rand(),rand(),rand()) for i in 1:x]
    generateT(x::Int64) = [(rand(),rand(),rand()) for i in 1:x]
    generateA(x::Int64) = [[rand(),rand(),rand()] for i in 1:x]

    function timing_and_allocation(X::Int64)
        S = generateS(X)
        T = generateT(X)
        A = generateA(X)
        println("structure vector:")
        @time start_profile(S)
        println("tuple vector:")
        @time start_profile(T)
        println("array vector:")
        @time start_profile(A)
    end
end        
