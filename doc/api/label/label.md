## Label

### `ctf_label_create`
Create a label.

#### Prototype
`ctf_label ctf_label_create(void)`

#### Arguments
None.

#### Return value
Allocated label object.

----------------------------------------------------

### `ctf_label_get_name`
Get label name.

#### Prototype
`int ctf_label_get_name(ctf_label label, char** name)`

#### Arguments
 * `label` label 
 * `name` output name of the label

#### Return value
 * `CTF_OK` on success
 * `CTF_E_NULL` if either `label` or `name` are `NULL`

----------------------------------------------------

### `ctf_label_set_name`
Set label name.

#### Prototype
`int ctf_label_set_name(ctf_label label, char* name)`

#### Arguments 
 * `label` label
 * `name` new name for the label

#### Return value 
 * `CTF_OK` on success
 * `CTF_E_NULL` if `label` is `NULL`

----------------------------------------------------

### `ctf_label_get_index`
Get label index.

#### Prototype
`int ctf_label_get_index(ctf_label label, ctf_label_index* index)`

#### Arguments 
 * `label` label
 * `index` index

#### Return value
 * `CTF_OK` on success
 * `CTF_E_NULL` if either `label` or `index` are `NULL`

----------------------------------------------------

### `ctf_label_set_index`
Set label index.

#### Prototype
`int ctf_label_set_index(ctf_label label, ctf_label_index index)`

#### Arguments 
 * `label` label
 * `index` index

#### Return value 
 * `CTF_E_NULL` if `label` is `NULL`

----------------------------------------------------

### `ctf_label_memory_usage`
Get number of bytes used by the label object.

#### Prototype
`size_t ctf_label_memory_usage(ctf_label label)`

#### Arguments
 * `label` label

#### Return value
Number of bytes used by the `label` object.


