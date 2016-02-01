module render
    using Images
    import geometry: Geometry, intersect, Sphere, Plane, Triangle
    import camera: Camera
    import ray: Ray, Screen, orthographicRay, perspectiveRay
    import sample2d: uniform2d, multi_jittered, hammersley
    import ImageView: view
    import Colors: RGB
    import vec3:Vec3f

    export Scene, renderScene, somerendering

    type Light
    end

    type Scene
        objects::Vector{Tuple{Geometry, RGB}} # currently there will be no material available
        lights::Vector{Light}
        camera::Camera
        screen::Screen
    end

    function somerendering()
        objects = Array{Tuple{Geometry, RGB}}(2)
        # objects[2] = (Sphere(1, (0.0, 0.0, 1000.0)), RGB(1, 1, 0))
        p1 = Vec3f(0, 2, 12)
        p2 = Vec3f(2, 0, 10)
        p3 = Vec3f(0, 0, 8)
        objects[1] = (Triangle(p1, p2, p3), RGB(0.0, 1.0, 0))
        p1 = Vec3f(0, 2, 10)
        p2 = Vec3f(2, 0, 10)
        p3 = Vec3f(0, 0, 10)
        objects[2] = (Triangle(p1, p2, p3), RGB(1.0, 0.0, 0.0))
        lights = Array(Light, 0)
        camera = Camera()
        screen = Screen(8, 20, 20)
        scene = Scene(objects, lights, camera, screen)
        data = renderScene(scene, uniform2d, 400)
        renderToImage(data)
    end

    function renderScene(scene::Scene, sample_methods::Function, resolution::Int)
        data = Array(RGB, (resolution, resolution))
        n = resolution
        samples = uniform2d(n)
        for x in 1:n
            for y in 1:n
                @inbounds ray = perspectiveRay(scene.screen, scene.camera, samples[x,y,1], samples[x,y,2])
                min_dist = Inf
                cur_colour = RGB(0,0,0) # something
                for (geo, colour) in scene.objects
                    dist = intersect(geo, ray)
                    if dist < min_dist
                        min_dist = dist
                        cur_colour = colour
                    end
                end
                data[x,y] = cur_colour
            end
        end
        return data
    end

    function renderToImage(data:: Array{RGB, 2})
        img = Image(data)
        view(img)
        return img
    end
end

