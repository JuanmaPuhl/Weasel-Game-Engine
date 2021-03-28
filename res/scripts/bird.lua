function on_create()
    limit_izq = -2600
    limit_der = -2300
    local level_1 = game_get_current_level()
    local entities_1 = level_get_entities(level_1)
    bird_damage_sprite = game_find_sprite("bird_damage")
    bird_sprite = game_find_sprite("bird")
    bird = entities_1[5]
    bird_music_component = entity_get_component(bird,"music")
    bird_sprite_attribute = entity_get_attribute(bird,"sprite")
    speed_bird = 96.0
    entity_scale(bird,-1.0,1.0,1.0)
    bird_count_hits = 45
    bird_life = 2
    bird_interludio = 100
    bird_ready = false
end

function on_update()
    if bird_being_hit then
        if bird_interludio == 0 then
            bird_being_hit = false
            attribute_set_sprite(bird_sprite_attribute,bird_sprite)
            bird_interludio = 100
        else
            bird_interludio = bird_interludio -1
        end
    end
    if bird_life == 0 and not bird_ready then
        bird_ready = true
        entity_set_position(bird,20000,10000,10000)
        return 1
    end
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

function on_collision(other)
    local entity_name = entity_get_name(other)
    if entity_name == "disparo" then
        if not bird_being_hit then
            
            if bird_count_hits == 0 then
                component_music_play_track(bird_music_component,false)
                bird_being_hit = true
                attribute_set_sprite(bird_sprite_attribute,bird_damage_sprite)
                bird_life = bird_life -1
            else
                bird_count_hits = bird_count_hits-1
            end
        end
    end
end