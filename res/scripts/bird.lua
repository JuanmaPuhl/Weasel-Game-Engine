function on_create()
    limit_izq = -2600
    limit_der = -2300
    local level_1 = game_get_current_level()
    local entities_1 = level_get_entities(level_1)
    bird = entities_1[5]
    speed_bird = 96.0
    entity_scale(bird,-1.0,1.0,1.0)
end

function on_update()
    local deltaTime = game_get_delta_time()
    bird_pos = entity_get_position(bird)
    if bird_pos[1] < limit_izq then
        speed_bird = 96.0
        entity_scale(bird,-1.0,1.0,1.0)
    end
    if bird_pos[1] > limit_der then
        speed_bird = -96.0
        entity_scale(bird,-1.0,1.0,1.0)
    end
    entity_translate(bird, speed_bird * deltaTime,0.0,0.0);
end

function on_collision()
end