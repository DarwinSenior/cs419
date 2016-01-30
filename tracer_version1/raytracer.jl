typealias Vec3{T} Tuple{T, T, T}
typealias Vec3f Vec3{Float32}


import Base: +, -, *
+(a::Vec3{Number}, b::Vec3{Number}) = (a[1]+b[1], a[2]+b[2], a[3]+b[3])
-(a::Vec3{Number}, b::Vec3{Number}) = (a[1]-b[1], a[2]-b[2], a[3]-b[3])
*(a::Number, b::Vec3{Number}) = (a*b[1], a*b[2], a*b[3])
*(b::Vec3{Number}, a::Number) = (a*b[1], a*b[2], a*b[3])
dot(a::Vec3{Number}, b::Vec3{Number}) = a[1]*b[1]+a[2]*b[2]+a[3]*b[3]
cross(a::Vec3{Number}, b::Vec3{Number}) = (a[2]*b[3]-a[3]*b[2], a[3]*a[1]-a[1]*b[3], a[1]*a[2]-a[2]*a[1])
norm(a::Vec3{Number}) = sqrt(a)


type Ray
    origin::Vec3f
    dir::Vec3f
end

abstract Geometry

immutable Sphere <: Geometry
    r::Float32
    origin::Vec3f
end

immutable Plane <: Geometry
    normal::Vec3f
    origin::Vec3f
end

immutable Triangle <: Geometry
    p0::Vec3f
    p1::Vec3f
    p2::Vec3f
end

type Camera
    origin::Vec3f
    up::Vec3f
    dir::Vec3f
end
