function on_create()
    basura_music_playing = false
    basura_falling = false
    basura_reactivada = false
    basura = level_get_entities(level)[55]
    basura_music_component = entity_get_component(basura,"music")
    basura_vspeed = 0.0
    basura_gravity = -350
end
function on_update()
    if basura_reactivada then
        basura_music_playing = false
        basura_falling = true
        basura_vspeed = 0.0
        local jim_position = entity_get_position(entity)
        entity_set_position(basura,jim_position[1],442.0,0.0)
        basura_reactivada = false
    end
    if basura_falling then
        local deltaTime = game_get_delta_time()
        entity_translate(basura,0.0, basura_gravity * deltaTime,0.0)
        basura_vspeed = basura_vspeed + basura_gravity
    end
end
function on_collision(other)
    local entity_name = entity_get_name(other)
    if entity_name == "floor" then
        if not basura_music_playing then
            component_music_play_track(basura_music_component,false)
            basura_music_playing = true
        end
    end
end
