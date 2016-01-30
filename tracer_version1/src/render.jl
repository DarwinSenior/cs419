module render
    using Images
    import geometry: Geometry, intersect
    import camera: Camera
    import ray: Ray, Screen, orthographicRay, perspectiveRay
    import sample: uniform2d, multi_jittered, hammersley
    export Scene, addToScene, render
    
    type Scene
        objects::Array{Tuple{Geometry, Color}}


end
