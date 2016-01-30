module vec3
    export Vec3, Vec3f, +, -, *, dot, cross, norm, normalise

    typealias Vec3{T} Tuple{T, T, T}
    typealias Vec3f Vec3{Float64}

    Vec3f(a,b,c) = (Float64(a),Float64(b),Float64(c))

    import Base: +, -, *, dot, cross, norm
    +{T<:Number}(a::Vec3{T}, b::Vec3{T}) = (a[1]+b[1], a[2]+b[2], a[3]+b[3])
    -{T<:Number}(a::Vec3{T}, b::Vec3{T}) = (a[1]-b[1], a[2]-b[2], a[3]-b[3])
    *{T<:Number}(a::T, b::Vec3{T}) = (a*b[1], a*b[2], a*b[3])
    *{T<:Number}(b::Vec3{T}, a::T) = (a*b[1], a*b[2], a*b[3])
    dot{T<:Number}(a::Vec3{T}, b::Vec3{T}) = a[1]*b[1]+a[2]*b[2]+a[3]*b[3]
    *{T<:Number}(a::Vec3{T}, b::Vec3{T}) = dot(a,b)
    cross{T<:Number}(a::Vec3{T}, b::Vec3{T}) = (a[2]*b[3]-a[3]*b[2], a[3]*b[1]-a[1]*b[3], a[1]*b[2]-a[2]*b[1])
    norm{T<:Number}(a::Vec3{T}) = sqrt(dot(a,a))
    normalise(x::Vec3f) = x*(1/norm(x))
end
