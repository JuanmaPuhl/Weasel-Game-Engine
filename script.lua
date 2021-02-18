-- Create an instance of sprite an call some methods

function on_update()
    
    print("Estoy en el on_update")
    entity = entity_new()
    entity_get_position(entity)
    entity_translate(entity,2,3,4)
    table = entity_get_position(entity)
    
    --Imprime la tabla que obtuve
    for k,v in ipairs( table ) do
        print(v)
    end
    
    component = entity_get_component(entity,0)
    print("A ver LUA")

    level = game_get_current_level()
    entity2 = level_add_entity(level)
    entity3 = level_add_entity(level)
    --printCantEntities(level)
    --print("A ver LUA")
    --addEntityLevel(level)
    entities = level_get_entities(level)
    --print(entities[1])
end