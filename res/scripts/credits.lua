function on_create()
    c_level = game_get_current_level()
    c_entities = level_get_entities(c_level)
    m = 0.0
    print(math.sin(math.pi/2))
    c_randoms = {}
    for i = 3, 39 do
        local r = math.random(50,75)
        c_randoms[i] = r
    end

end
function on_update()
    m = m + 0.001
    print(m)
    for i = 3, 39 do
            entity_translate(c_entities[i],0.0,(math.sin(math.deg(m))*c_randoms[i])*game_get_delta_time(),0.0)
    end
end
function on_collision(other)
end