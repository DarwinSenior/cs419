module geometry
    importall vec3
    import Base: intersect
    import ray: Ray
    export Geometry, Sphere, Plane,Triangle, intersect
    abstract Geometry

    immutable Sphere <: Geometry
        r::Float64
        center::Vec3f
    end
    """
    norm = (A,B,C)
    |norm| = 1 and does not checked
    norm*x+dist=0 as the equation
    """
    immutable Plane <: Geometry
        norm::Vec3f
        dist::Float64
    end

    immutable Triangle <: Geometry
        p0::Vec3f
        p1::Vec3f
        p2::Vec3f
    end

    """
    solve, return the -Inf,+Inf for complex solution
    """
    function solve_quad(a, b, c)
        delta = b^2-4a*c
        if delta<0
            return -Inf, Inf
        end
        sqrt_delta = sqrt(delta)
        return (-b-sqrt_delta)/2a, (-b+sqrt_delta)/2a
    end
    """
    intersect with the sphere, it should result to two point (real or imaginary)
    however, we will only interested in the nearest positive point,
    if point does not exists, return +infinity
    """
    function intersect(sphere::Sphere, ray::Ray)
        println("tested")
        a = dot(ray.dir, ray.dir)
        o_c = ray.origin-sphere.center
        b = 2.0*dot(o_c, ray.dir)
        c = dot(o_c, o_c)
        dist1, dist2 = solve_quad(a, b, c)
        if dist1>0
            return dist1
        elseif dist2>0
            return dist2
        else
            return Inf
        end
    end

    """
    intersect with the plane, it will return the nearest positive point or +infinity
    """
    function intersect(plane::Plane, ray::Ray)
        dist = (plane.dist-dot(ray.origin, plane.norm))/dot(ray.origin, plane.norm)
        return dist>0 ? dist : Inf
    end


    """
    test if the result is inside the triangle
    It is also a Barycentric Technique,
    found on the web
    http://www.blackpawn.com/texts/pointinpoly/
    """
    function inside_triangle(t::Triangle, p::Vec3f)
        # Compute vectors
        v0 = t.p2-t.p0
        v1 = t.p1-t.p0
        v3 = p-t.p0

        # Compute dot products
        dot00 = dot(v0, v0)
        dot01 = dot(v0, v1)
        dot02 = dot(v0, v2)
        dot11 = dot(v1, v1)
        dot12 = dot(v1, v2)

        # Compute barycentric coordinates
        inv_denom = 1 / (dot00 * dot11 - dot01 * dot01)
        u = (dot11 * dot02 - dot01 * dot12) * inv_denom
        v = (dot00 * dot12 - dot01 * dot02) * inv_denom

        # Check if point is in triangle
        return (u >= 0) && (v >= 0) && (u + v < 1)
    end
    """
    intersect with the triangle, return the nearest positive point or +infinity
    """
    function intersect(triangle::Triangle, ray::Ray)
        n = cross(triangle.p0-triangle.p1, triangle.p0-triangle.p2)
        d = norm(triangle.p0)/dot(n, triangle.p0)
        dist = (d-dot(ray.origin, n))/dot(ray.origin, n)
        if dist<0 || !inside_triangle(triangle, ray.origin+dist*ray.dir)
            return Inf
        else
            return dist
        end
    end

end
