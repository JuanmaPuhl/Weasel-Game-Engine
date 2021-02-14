-- Create an instance of sprite an call some methods

function on_update()
    print("Estoy en el on_update")
    entity = entity_new()
    entity_get_position(entity)
    entity_translate(entity,2,3,4)
    table = entity_get_position(entity)
    --Imprime la tabla que obtuve
    --for k,v in ipairs( table ) do
    --    print(v)
    --end
    
    local component = entity_get_component(entity,0)
    print(table[1])
    print(component)
end