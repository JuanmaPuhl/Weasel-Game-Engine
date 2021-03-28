function on_create()
    billy = level_get_entities(level)[17]
    bin_activated = false
    bin_falling = true
    bin_vspeed = 0
    bin_sprite_attribute = entity_get_attribute(billy,"sprite")
    bin_current_sprite = attribute_get_sprite(bin_sprite_attribute)
    
    print(bin_initial_sprite_speed)
    bin_falling_animation = game_find_sprite("robot_falling")
    bin_attack_animation = game_find_sprite("robot_attack")
    bin_initial_sprite_speed = sprite_get_speed(bin_attack_animation)
    bin_music_component = entity_get_component(billy,"music")
    bin_basura_music_component = entity_get_component(billy, "music2")
    bin_play_sound = false
    bin_attack_counter = 0
    being_hit = false
    bin_life = 10
    ready = false
    count_hits = 45
    bin_explosion_sprite = game_find_sprite("explosion")
    fin = false
end
function on_update()
    if bin_activated then
        --sprite_set_speed(bin_current_sprite,bin_initial_sprite_speed)
    end
    if bin_activated and bin_falling then
        print("entre")
        local deltaTime = game_get_delta_time()
        entity_translate(billy,0.0, bin_vspeed * deltaTime,0.0)
        bin_vspeed = bin_vspeed + gravity
    end
    if not bin_falling and bin_activated then
        local bin_current_sprite_index = sprite_get_current_image(bin_current_sprite) 
        if bin_current_sprite_index == 5 and not bin_play_sound then
            bin_play_sound = true
            component_music_set_volume(bin_basura_music_component,0.6)
            component_music_play_track(bin_music_component,false)
            bin_attack_counter = bin_attack_counter + 1
            count_hits = 45
            being_hit = false
        end
        if bin_current_sprite_index ~= 5 then
            bin_play_sound = false
            
        end
        if bin_attack_counter == 3 then
            --component_music_play_track(bin_basura_music_component,false)
            basura_reactivada = true
            bin_attack_counter = 0
        end
        
    end 
    if bin_life == 0 and not ready then
        bin_activated = false
        ready = true
        attribute_set_sprite(bin_sprite_attribute,bin_explosion_sprite)
        component_music_play_track(bin_music_component,false)
    end
    if ready and not fin then
        local curr_spr = attribute_get_sprite(bin_sprite_attribute)
        local curr_index = sprite_get_current_image(curr_spr)
        if curr_index == 6 then
            entity_set_position(billy,10000,10000,10000)
            fin = true
        end
    end

end
function on_collision(other)
    local entity_name = entity_get_name(other)
    if entity_name == "floor" then
        if bin_falling then
            bin_falling = false
            local collision_position = entity_get_position(other)
            local entiy_pos = entity_get_position(billy)
            entity_translate(billy,0,1,0)
            bin_vspeed = 0
        end
    end
    if entity_name == "disparo" then
        if not being_hit then
            
            if count_hits == 0 then
                component_music_play_track(bin_basura_music_component,false)
                being_hit = true
                sprite_restart(bin_current_sprite)
                bin_life = bin_life -1
                log_print(bin_life)
            else
                count_hits = count_hits-1
            end
        end
    end
    
end